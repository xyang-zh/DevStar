#include "pch.h"

#include "MemorySpace.h"
#if __has_include("MemorySpace.g.cpp")
#include "MemorySpace.g.cpp"
#endif

#include <boost/format.hpp>
#include <boost/tokenizer.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/xpressive/xpressive.hpp>

#include "LibraryResources.h"
#include "FallSerializationHelpers.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

static const char* UnitTag{ "BbKkMmGgTt" };
static const char* NumberTag{ "0123456789." };
static const std::wstring_view SizeTag{ L"0123456789.BbKkMmGgTt" };
static const char* SeparatorTag{ " ,\r" };
static const std::wstring_view globalTag{ L"0123456789.BbKkMmGgTt ,\r" };
static const std::wstring_view warningTag{ L"不支持的字符" };


namespace winrt::DevStar::implementation
{
	MemorySpace::MemorySpace()
	{
	}

	void MemorySpace::MemorySpaceTextChanged(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::Controls::TextChangedEventArgs const& /*e*/)
	{
		auto size = MemorySpaceBox().Text();
		UpdateSize(size);
	}

	void MemorySpace::ClearButtonClicked(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::RoutedEventArgs const& /*e*/)
	{
		winrt::hstring empty{ L"" };

		MemorySpaceBox().Text(empty);
		UpdateSize(empty);
	}

	bool MemorySpace::SizeValid(winrt::hstring& p)
	{
		auto str = winrt::to_string(p);

		if ((str.find_first_not_of(winrt::to_string(globalTag)) == std::string::npos))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	double MemorySpace::UnitSize(std::string p)
	{
		if (p == "B" || p == "b")
		{
			return 1.0;
		}
		else if (p == "K" || p == "k")
		{
			return 1000.0;
		}
		else if (p == "M" || p == "m")
		{
			return 1000000.0;
		}
		else if (p == "G" || p == "g")
		{
			return 1000000000.0;
		}
		else if (p == "T" || p == "t")
		{
			return 1000000000000.0;
		}
		else
		{
			return 0;
		}
	}

	void MemorySpace::UpdateSize(winrt::hstring& p)
	{
		bool valid{ true };
		winrt::hstring unit, total;
		double size{ 0 }, value{ 0 }, multp{ 0 };
		std::vector<std::string> sizeList;

		if (p.empty())
		{
			return MemorySpaceTotal().Text(L"");
		}

		if (!SizeValid(p))
		{
			return MemorySpaceTotal().Text(warningTag);			
		}

		const auto str = winrt::to_string(p);
		boost::char_separator<char> sep{ SeparatorTag };
		boost::tokenizer<boost::char_separator<char>> token(str, sep);

		boost::split(sizeList, winrt::to_string(p), boost::is_any_of(SeparatorTag), 
															boost::token_compress_on);
		sizeList.erase(std::remove_if(sizeList.begin(), sizeList.end(), [](const std::string& str) { 
																			return str == "";
																		}), sizeList.end());

		for (auto iter = sizeList.begin(); iter != sizeList.end();)
		{
			if (*iter == "") { iter++; continue; }

			auto next = iter;

			if (++next == sizeList.end())
			{
				auto _str = std::string{ *iter };
				boost::smatch match;
				boost::regex regx_numb{ "(\\d+)" }, regx_unit{ "([BbKkMmGgTt])" };

				if (boost::regex_search(_str, match, regx_numb))
				{
					auto _vl = match[0].str();
					value = std::stod(_vl);
				}
				if (boost::regex_search(_str, match, regx_unit))
				{
					auto _unit = match[0].str();
					multp = UnitSize(_unit);
					value *= multp;
				}
				size += value;

				iter++;
			}
			else
			{
				auto _vl = *iter;
				auto _next = *next;

				if (_vl.find_first_not_of(NumberTag) == std::string::npos && 
					_next.find_first_not_of(UnitTag) == std::string::npos)
				{
					value = std::stod(_vl), multp = UnitSize(_next);
					value *= multp;
					iter = ++next;
				}
				else if (_vl.find_first_not_of(NumberTag) == std::string::npos && 
						 _next.find_first_not_of(NumberTag) == std::string::npos)
				{
					value = std::stod(_vl);
					iter++;
				}
				else if (_vl.find_first_not_of(winrt::to_string(SizeTag)) == std::string::npos)
				{
					auto _str = std::string{ *iter };
					boost::smatch match;
					boost::regex regx_numb{ "(\\d+)" }, regx_unit{ "([BbKkMmGgTt])" };

					if (boost::regex_search(_str, match, regx_numb))
					{
						_vl = match[0].str();
						value = std::stod(_vl);
					}
					if (boost::regex_search(_str, match, regx_unit))
					{
						auto _unit = match[0].str();
						multp = UnitSize(_unit);
						value *= multp;
					}
					size += value;

					iter++;
				}
				else
				{
					valid = false;
					break;
				}
				size += value;
			}
		}

		if (valid == false)
		{
			MemorySpaceTotal().Text(warningTag);
			return;
		}

		if (size >= 0.0 && size <= 1000)
		{
			unit = L"B";			
		}
		else if (size > 1000 && size <= 1000000)
		{
			unit = L"K";
			size = size / 1000;
		}
		else if (size > 1000000 && size <= 1000000000)
		{
			unit = L"M";
			size = size / 1000000;
		}
		else if (size > 1000000000 && size <= 1000000000000)
		{
			unit = L"G";
			size = size / 1000000000;
		}
		else
		{
			unit = L"T";
			size = size / 1000000000000;
		}

		total = winrt::to_hstring((boost::format("%.3f") %size).str()) + L" " + unit;

		MemorySpaceTotal().Text(total);
	}
}
