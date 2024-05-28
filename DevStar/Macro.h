#pragma once

#include "Macro.g.h"
#include "Utils.h"
#include "ViewModelHelpers.h"

namespace winrt::DevStar::implementation
{
    struct Macro : MacroT<Macro>
    {
        Macro();

        GETSET_BINDABLE_ENUM_SETTING(Method, Windows::Foundation::Collections::IObservableVector<winrt::hstring>, L"Nearest");
        GETSET_BINDABLE_ENUM_SETTING(ImplMode, Windows::Foundation::Collections::IObservableVector<winrt::hstring>, L"Auto");

    public:
        void MethodSelectionChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void ImplModeSelectionChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void MacroClearClicked(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);
        void MacroImplCopyClicked(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);
        void MacroTextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e);
    
    public:
        void onMacroChanged(void);
        void CompleteMacro(std::string& s, winrt::hstring& mode, winrt::hstring& align);
    };
}

namespace winrt::DevStar::factory_implementation
{
    struct Macro : MacroT<Macro, implementation::Macro>
    {
    };
}
