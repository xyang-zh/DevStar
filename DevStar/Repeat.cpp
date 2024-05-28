#include "pch.h"

#include "Repeat.h"
#if __has_include("Repeat.g.cpp")
#include "Repeat.g.cpp"
#endif

#include <unordered_set>
#include <boost/format.hpp>
#include <boost/tokenizer.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>

#include "LibraryResources.h"
#include "FallSerializationHelpers.h"

using namespace std;
using namespace winrt;
using namespace Windows::UI::Xaml;

using namespace Windows::UI;
using namespace Windows::UI::Core;
using namespace Windows::UI::Text;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::ViewManagement;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel::Core;

static const std::wstring_view separatorTag{ L" ,\r" };
static const std::wstring_view autoSearchTag{ L"auto" };
static const std::wstring_view manualSearchTag{ L"manual" };
static const std::wstring_view emptyTag{ L"空" };
static const std::wstring_view zeroTag{ L"0." };

namespace winrt::DevStar::implementation
{
	Repeat::Repeat()
	{
	}

	void Repeat::AutoSearch(bool v)
	{
		_autoSearch = v;
		if (v == true)
		{
			FindBox().IsEnabled(false);
		}
		else
		{
			FindBox().IsEnabled(true);
		}
	}

	bool Repeat::AutoSearch(void)
	{
		return _autoSearch;
	}

	void Repeat::HighlightMatches(winrt::hstring& p)
	{
		winrt::hstring textToFind = p;
		Windows::UI::Color highlightBackgroundColor = Windows::UI::Xaml::Application::Current().Resources().TryLookup(
													  winrt::box_value(L"SystemColorHighlightColor")).as<Windows::UI::Color>();
		Windows::UI::Color highlightForegroundColor = Windows::UI::Xaml::Application::Current().Resources().TryLookup(
													  winrt::box_value(L"SystemColorHighlightTextColor")).as<Windows::UI::Color>();
		if (!p.empty())
		{
			Windows::UI::Text::ITextRange searchRange = Editor().Document().GetRange(0, 0);
			while (searchRange.FindText(textToFind, 
										Windows::UI::Text::TextConstants::MaxUnitCount(),
										Windows::UI::Text::FindOptions::Word) > 0)
			{
				searchRange.CharacterFormat().BackgroundColor(highlightBackgroundColor);
				searchRange.CharacterFormat().ForegroundColor(highlightForegroundColor);
			}
		}
	}

	void Repeat::RemoveHighlightes(void)
	{
		Windows::UI::Text::ITextRange documentRange = Editor().Document().
													  GetRange(0, Windows::UI::Text::TextConstants::MaxUnitCount());
		Windows::UI::Xaml::Media::SolidColorBrush defaultBackground = Editor().Background().as
																	  <Windows::UI::Xaml::Media::SolidColorBrush>();
		Windows::UI::Xaml::Media::SolidColorBrush defaultForeground = Editor().Foreground().as
																	  <Windows::UI::Xaml::Media::SolidColorBrush>();

		documentRange.CharacterFormat().BackgroundColor(defaultBackground.Color());
		documentRange.CharacterFormat().ForegroundColor(defaultForeground.Color());
	}

	void Repeat::RemoveStatistics(void)
	{
		Total().Text(zeroTag);
		Repeater().Text(emptyTag);
	}

	void Repeat::ProcessRepeat(std::string& p, std::string& match, winrt::hstring& method)
	{
		std::vector<std::string> repeatList;
		std::unordered_set<std::string> sets, repeats;		

		if (method == autoSearchTag)
		{
			boost::split(repeatList, p, boost::is_any_of(separatorTag), boost::token_compress_on);
			repeatList.erase(std::remove_if(repeatList.begin(), repeatList.end(), [](const std::string& str) { 
																				      return str.empty();
																				  }), repeatList.end());
			for (auto& v : repeatList)
			{
				if (sets.find(v) != sets.end())	{ repeats.insert(v); }
				else { sets.insert(v); }
			}
		}
		else if (method == manualSearchTag)
		{
			if (p.find(match) != p.npos)
			{
				repeats.insert(match);
				repeatList.emplace_back(p);
			}
		}
		else
		{
			return;
		}

		if ((repeats.empty() && RecordsEmpty()) || RepeatSame(repeats, repeatList.size()))
		{
			return;
		}
		else if (repeats.empty() && !RecordsEmpty())
		{
			ClearRecords();
			RemoveHighlightes();
			RemoveStatistics();
			return;
		}
		
		{
			RemoveHighlightes();
			UpdateRecords(repeats, repeatList.size());
			for (auto& v : repeats)
			{
				winrt::hstring highlight = winrt::to_hstring(v);
				HighlightMatches(highlight);
			}
		
			winrt::hstring _repeater = winrt::to_hstring(boost::algorithm::join(repeats, " "));
			Repeater().Text(_repeater);

			const auto num = winrt::to_hstring(repeats.size());
			Total().Text(num);
		}
	}

	void Repeat::RepeatTextChanged(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Windows::UI::Xaml::RoutedEventArgs const& /*e*/)
	{
		if (!AutoSearch()) { return; }

		std::string match{ "" };
		winrt::hstring method { L"auto" };
		std::string text = winrt::to_string(Editor().Document().GetRange(0, Windows::UI::Text::TextConstants::MaxUnitCount()).Text());

		ProcessRepeat(text, match, method);
	}

	void Repeat::FindBoxTextChanged(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& /*e*/)
	{
		winrt::hstring method{ L"manual" };
		std::string match{ winrt::to_string(FindBox().Text()) };
		std::string text = winrt::to_string(Editor().Document().GetRange(0, Windows::UI::Text::TextConstants::MaxUnitCount()).Text());

		ProcessRepeat(text, match, method);		
	}

	void Repeat::ClearButtonClicked(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::RoutedEventArgs const& /*e*/)
	{
		std::string match{ "" };
		winrt::hstring method{ L"none" };
		winrt::hstring empty{ L"" };
		std::string text{ "" };

		Editor().Document().SetText(Windows::UI::Text::TextSetOptions::None, empty);
		ProcessRepeat(text, match, method);
	}

	bool Repeat::RepeatSame(std::unordered_set<std::string>& v, size_t s)
	{
		if (_repeatSet == v && _repeatNum == s)	{ return true; }

		return false;
	}

	bool Repeat::RecordsEmpty()
	{
		return _repeatSet.size() == 0 ? true : false;
	}

	void Repeat::ClearRecords(void)
	{
		_repeatSet.clear();
		_repeatNum = 0;
	}

	void Repeat::UpdateRecords(std::unordered_set<std::string>& v, size_t s)
	{
		if (v.size() == 0 || s == 0) { return; }

		_repeatSet = v;
		_repeatNum = s;
	}
}
