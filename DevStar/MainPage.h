#pragma once

#include "MainPage.g.h"
//#include "Utils.h"

namespace winrt::DevStar::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
    public:
        MainPage();
        void SettingsNav_ItemInvoked(const Microsoft::UI::Xaml::Controls::NavigationView& sender, const Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs& args);
        void SettingsNav_DisplayModeChanged(const Microsoft::UI::Xaml::Controls::NavigationView& sender, const Microsoft::UI::Xaml::Controls::NavigationViewDisplayModeChangedEventArgs& args);
        void SettingsNav_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

    private:
        void _Navigate(hstring clickedItemTag, hstring subPage);
    };
}

namespace winrt::DevStar::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
