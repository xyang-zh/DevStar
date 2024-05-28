#pragma once

#include "Accumulate.g.h"
#include "Utils.h"
#include "ViewModelHelpers.h"

namespace winrt::DevStar::implementation
{
    struct Accumulate : AccumulateT<Accumulate>, ViewModelHelper<Accumulate>
    {
        Accumulate();

        GETSET_BINDABLE_ENUM_SETTING(Method, Windows::Foundation::Collections::IObservableVector<winrt::hstring>, L"Default");

    public:
        void RangeClearClicked(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);
        void CustomClearClicked(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);
        void Method_SelectionChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void Custom_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e);
        void Scale_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e);        

    public:
        void ClearAdd(void);
        bool isScaleValid(std::vector<std::string>& v, winrt::hstring& m);
        void scaleContentChanged(void);
        winrt::hstring Add(int64_t b, int64_t e, int64_t s, winrt::hstring& mode);
        void UpdateAdd(std::string& b, std::string& e, std::string& s, winrt::hstring& method);
    };
}

namespace winrt::DevStar::factory_implementation
{
    struct Accumulate : AccumulateT<Accumulate, implementation::Accumulate>
    {
    };
}
