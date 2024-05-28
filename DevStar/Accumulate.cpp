#include "pch.h"

#include "Accumulate.h"
#if __has_include("Accumulate.g.cpp")
#include "Accumulate.g.cpp"
#endif

#include "LibraryResources.h"
#include "FallSerializationHelpers.h"

#include <boost/format.hpp>
#include <boost/tokenizer.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/xpressive/xpressive.hpp>

using namespace std;
using namespace winrt;
using namespace Windows::UI::Xaml;

static const char* NumberTag{ "-0123456789" };
static const char* SeparatorTag{ " ,\r" };
static const std::wstring_view  defaultTag{ L"默认" };
static const std::wstring_view  oddTag{ L"奇数" };
static const std::wstring_view  evenTag{ L"偶数" };
static const std::wstring_view  customTag{ L"自定义" };
static const std::wstring_view  invalidTag{ L"无效" };
static const std::wstring_view  emptyTag{ L"" };
static const std::wstring_view  zeroTag{ L"0" };

namespace winrt::DevStar::implementation
{
	Accumulate::Accumulate()
	{
		INITIALIZE_BINDABLE_ENUM_SETTING(Method, Methods, L"Content");
	}

	void Accumulate::RangeClearClicked(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::RoutedEventArgs const& /*e*/)
	{
		Begin().Text(emptyTag);
		End().Text(emptyTag);
		AddSummary().Text(zeroTag);
	}

	void Accumulate::CustomClearClicked(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::RoutedEventArgs const& /*e*/)
	{
		Custom().Text(emptyTag);
		AddSummary().Text(zeroTag);
	}

	void Accumulate::Method_SelectionChanged(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& /*e*/)
	{
		scaleContentChanged();
	}

	void Accumulate::Custom_TextChanged(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& /*e*/)
	{
		scaleContentChanged();
	}

	winrt::hstring Accumulate::Add(int64_t b, int64_t e, int64_t s, winrt::hstring& mode)
	{
		int64_t i{ 0 }, add{ 0 };	

		if (mode == customTag && (s < 0 && b <= e) || (b + s) > e)
		{
			return winrt::hstring{ invalidTag };
		}

		for (i = b; i <= e;)
		{
			if (mode == defaultTag)
			{
				add += i;
				i += 1;
			}
			else if (mode == oddTag)
			{
				if ((i & 1ULL) == 1) { add += i; i += 2; }
				else { i += 1; add += i; }
			}
			else if (mode == evenTag)
			{
				if ((i & 1ULL) == 1) { i += 2; add += i; }
				else { add += i; i += 2; }
			}
			else
			{
				add += i;
				i += s;
			}
		}

		return winrt::to_hstring(add);
	}

	void Accumulate::UpdateAdd(std::string& b, std::string& e, std::string& s, winrt::hstring& method)
	{
		int64_t _b, _e, _s;

		try
		{
			_b = stoll(b, nullptr, 10);
			_e = stoll(e, nullptr, 10);
			_s = method == customTag ? stoll(s, nullptr, 10) : 0LL;			
		}
		catch (...)
		{ 
			AddSummary().Text(invalidTag); 
			return;
		}

		auto add = Add(_b, _e, _s, method);
		AddSummary().Text(add);
	}

	void Accumulate::ClearAdd(void)
	{
		AddSummary().Text(emptyTag);
	}

	bool Accumulate::isScaleValid(std::vector<std::string>& v, winrt::hstring& m)
	{
		std::vector<std::string> beginNumList;
		std::vector<std::string> endNumList;
		std::string begin{ winrt::to_string(Begin().Text()) };
		std::string end{ winrt::to_string(End().Text()) };
		std::vector<std::string> intervalNumList;
		std::string interval{ winrt::to_string(Custom().Text()) };

		boost::split(beginNumList, begin, boost::is_any_of(SeparatorTag), boost::token_compress_on);
		beginNumList.erase(std::remove_if(beginNumList.begin(),
										  beginNumList.end(),
										  [](const std::string& str) {
												return str.empty();
										  }), 
						   beginNumList.end());

		boost::split(endNumList, end, boost::is_any_of(SeparatorTag), boost::token_compress_on);
		endNumList.erase(std::remove_if(endNumList.begin(), 
										endNumList.end(), 
										[](const std::string& str) {
											return str.empty();
										}),	
						endNumList.end());

		boost::split(intervalNumList, interval, boost::is_any_of(SeparatorTag), boost::token_compress_on);
		intervalNumList.erase(std::remove_if(intervalNumList.begin(), 
											 intervalNumList.end(), 
											 [](const std::string& str) {
												return str.empty();
											 }), 
							  intervalNumList.end());

		if (beginNumList.empty() || endNumList.empty())
		{
			ClearAdd();
			return false;
		}
		else if (beginNumList[0] == "-" || endNumList[0] == "-")
		{
			return false;
		}
		else if (beginNumList[0].find_first_not_of(NumberTag) != std::string::npos || endNumList[0].find_first_not_of(NumberTag) != std::string::npos)
		{
			return false;
		}
		else if (m == customTag && intervalNumList.empty())
		{
			ClearAdd();
			return false;
		}
		else if (m == customTag && intervalNumList[0] == "-")
		{
			return false;
		}
		else if (m == customTag && intervalNumList[0].find_first_not_of(NumberTag) != std::string::npos)
		{
			return false;
		}
		else
		{
			const string _b{ beginNumList[0] };
			const string _e{ endNumList[0] };
			const string _s{ m == customTag ? intervalNumList[0] : "" };

			v.emplace_back(_b);
			v.emplace_back(_e);
			v.emplace_back(_s);
			return true;
		}
	}

	void  Accumulate::scaleContentChanged(void)
	{
		winrt::hstring method{ winrt::unbox_value<winrt::hstring>(CurrentMethod()) };
		std::vector<std::string> scale;

		if (method == customTag && Custom().IsEnabled() == false) {
			Custom().IsEnabled(true);
		}
		else {
			Custom().IsEnabled(false);
		}
		const auto vaild = isScaleValid(scale, method);
		if (vaild)
		{
			std::string begin = scale[0];
			std::string end = scale[1];
			std::string interval = scale[2];

			UpdateAdd(begin, end, interval, method);
		}
	}

	void Accumulate::Scale_TextChanged(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& /*e*/)
	{
		scaleContentChanged();
	}
}

UTILS_DEFINE_LIBRARY_RESOURCE_SCOPE(L"Resources");
