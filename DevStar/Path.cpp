#include "pch.h"

#include "Path.h"
#if __has_include("Path.g.cpp")
#include "Path.g.cpp"
#endif

#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

using namespace winrt;
using namespace Windows::UI::Xaml;

static const std::wstring_view SeparatorSlashTag{ L"\\" };
static const std::wstring_view SeparatorBackslashTag{ L"/"};
static const std::wstring_view LinuxTag{ L"Linux" };
static const std::wstring_view WindowsTag{ L"Windows" };
static const std::wstring_view EmptyTag{ L"" };

namespace winrt::DevStar::implementation
{
	Path::Path()
	{
	}

	void Path::PathPanel_Loaded(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::RoutedEventArgs const& /*e*/)
	{
	}

	void Path::SystemChanged(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& /*e*/)
	{
		auto path = PathInput().Text();
		UpdatePath(path);
	}

	void Path::PathTextChanged(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& /*e*/)
	{
		auto path = PathInput().Text();
		UpdatePath(path);
	}

	void Path::ClearButtonClicked(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Windows::UI::Xaml::RoutedEventArgs const& /*e*/)
	{	
		winrt::hstring empty{ L"" };

		PathInput().Text(empty);
		UpdatePath(empty);
	}

	void Path::UpdatePath(winrt::hstring& p)
	{
		if (p.empty())
		{
			PathTransSingle().Text(L"");
			PathTransDual().Text(L"");
			return;
		}

		std::string path{ winrt::to_string(p) };
		std::vector<std::string> pathList;
		winrt::hstring beginSep{ L"" }, endSep{ L"" }, betSep{ L"" };
		winrt::hstring SingleSepPath{ L"" }, DualSepPath{ L"" };

		if (boost::contains(p, SeparatorSlashTag) || boost::contains(p, SeparatorBackslashTag))
		{
			if (winrt::unbox_value<winrt::hstring>(ViewModel().CurrentSystem()) == LinuxTag)
			{
				betSep = L"/";
			}
			else if (winrt::unbox_value<winrt::hstring>(ViewModel().CurrentSystem()) == WindowsTag)
			{
				betSep = L"\\";
			}
			if (winrt::hstring{ p[0] } == SeparatorSlashTag || winrt::hstring{ p[0] } == SeparatorBackslashTag)
			{
				beginSep = betSep;
			}
			if (p.size() > 1 && (winrt::hstring{ p.back() } == SeparatorSlashTag || winrt::hstring{ p.back() } == SeparatorBackslashTag))
			{
				endSep = betSep;
			}

			SingleSepPath = beginSep;
			DualSepPath = beginSep + beginSep;
			boost::split(pathList, winrt::to_string(p), boost::is_any_of("\\,/"), boost::token_compress_on);
			for (size_t i = 0; i < pathList.size(); i++)
			{
				if (pathList[i] == "")
				{
					continue;
				}

				SingleSepPath = SingleSepPath + winrt::to_hstring(pathList[i]);
				DualSepPath = DualSepPath + winrt::to_hstring(pathList[i]);
				if (i != pathList.size() - 1 && pathList[i+1] != "")
				{
					SingleSepPath = SingleSepPath + betSep;
					DualSepPath = DualSepPath + betSep + betSep;
				}
			}
			if (!endSep.empty())
			{
				SingleSepPath = SingleSepPath + endSep;
				DualSepPath = DualSepPath + endSep + endSep;
			}
		}
		else
		{
			SingleSepPath = DualSepPath = p;
		}

		PathTransSingle().Text(SingleSepPath);
		PathTransDual().Text(DualSepPath);
	}
}
