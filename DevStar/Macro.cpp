#include "pch.h"

#include "Macro.h"
#if __has_include("Macro.g.cpp")
#include "Macro.g.cpp"
#endif

#include "LibraryResources.h"
#include "FallSerializationHelpers.h"

#include <unordered_set>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>

using namespace winrt;
using namespace Windows::UI::Xaml;

static const std::wstring_view SeparatorTag{ L"\r" };
static const std::wstring_view nearestTag{ L"最近处" };
static const std::wstring_view bymaxTag{ L"根据长度对齐" };
static const std::wstring_view autoTag{ L"自动" };
static const std::wstring_view allTag{ L"强制补全" };
static const std::wstring_view emptyTag{ L"" };


namespace winrt::DevStar::implementation
{
    Macro::Macro()
    {
        INITIALIZE_BINDABLE_ENUM_SETTING(Method, ImplMethods, L"Content");
        INITIALIZE_BINDABLE_ENUM_SETTING(ImplMode, ImplModes, L"Content");
    }

    void Macro::MethodSelectionChanged(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& /*e*/)
    {
        onMacroChanged();
    }

    void Macro::ImplModeSelectionChanged(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& /*e*/)
    {
        onMacroChanged();
    }

    void Macro::MacroClearClicked(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::RoutedEventArgs const& /*e*/)
    {
        onMacroChanged();
    }

    void Macro::MacroImplCopyClicked(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::RoutedEventArgs const& /*e*/)
    {
        std::string _string{ winrt::to_string(MacroImpl().Text()) };
        _string.pop_back();
        winrt::hstring text{ winrt::to_hstring(_string) };

        Windows::ApplicationModel::DataTransfer::DataPackage dataPackage{ Windows::ApplicationModel::DataTransfer::DataPackage() };
        dataPackage.SetText(text);

        Windows::ApplicationModel::DataTransfer::Clipboard::SetContent(dataPackage);
    }

    void Macro::MacroTextChanged(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& /*e*/)
    {
        onMacroChanged();
    }

    void Macro::onMacroChanged(void)
    {
        std::string macro{ winrt::to_string(MacroBox().Text()) };
        winrt::hstring align{ winrt::unbox_value<winrt::hstring>(CurrentMethod()) };
        winrt::hstring mode{ winrt::unbox_value<winrt::hstring>(CurrentImplMode()) };

        CompleteMacro(macro, mode, align);
    }

    void Macro::CompleteMacro(std::string& s, winrt::hstring& mode, winrt::hstring& align)
    {
        size_t  maxlength{ 0 };
        size_t  implenum{ 0 };
        std::string text{ "" };
        std::string last{ "" };
        winrt::hstring macros{ L"" };
        std::vector<std::string> sections;

        if (s.empty())
        {
            return MacroImpl().Text(emptyTag);
        }

        boost::split(sections, s, boost::is_any_of(SeparatorTag), boost::token_compress_on);
        for (const auto& v : sections)
        { 
            if (v.size() > maxlength) { maxlength = v.size(); }
        }
        implenum = sections.size();
        if (mode == autoTag && implenum > 1)
        {
            implenum--;
            last = sections.back();
        }

        if (align == bymaxTag)
        {
            int32_t spacesnum{ 0 };
            for (size_t i = 0; i < implenum; i++)
            {
                text = sections[i];
                spacesnum = (int32_t)(maxlength - sections[i].size());

                for (int32_t j = 0; j < spacesnum; j++) {  text += " "; }
                macros = macros + winrt::to_hstring(text) + L" \\" + L"\r";
            }
        }
        else
        {
            for (size_t i = 0; i < implenum; i++)
            {
                text = sections[i];
                macros = macros + winrt::to_hstring(text) + L" \\" + L"\r";
            }
        }
        macros = macros + winrt::to_hstring(last);

        MacroImpl().Text(macros);
    }
}
