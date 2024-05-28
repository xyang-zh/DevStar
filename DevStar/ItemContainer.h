#pragma once

#include "ItemContainer.g.h"
#include "Utils.h"

namespace winrt::DevStar::implementation
{
    struct ItemContainer : ItemContainerT<ItemContainer>
    {
    public:
        ItemContainer();

        void OnApplyTemplate();

        DEPENDENCY_PROPERTY(Windows::Foundation::IInspectable, Header);
        DEPENDENCY_PROPERTY(hstring, HelpText);
        DEPENDENCY_PROPERTY(hstring, CurrentValue);
        //DEPENDENCY_PROPERTY(bool, HasSettingValue);
        DEPENDENCY_PROPERTY(bool, StartExpanded);
        //DEPENDENCY_PROPERTY(IInspectable, SettingOverrideSource);

        winrt::event_token ClearSettingValue(const winrt::Windows::Foundation::TypedEventHandler<DevStar::ItemContainer, Windows::Foundation::IInspectable>& handler)
        {
            return _ClearSettingValueHandlers.add(handler);
        }

        void ClearSettingValue(const winrt::event_token& token)
        {
            _ClearSettingValueHandlers.remove(token);
        }

    private:
        static void _InitializeProperties();
        //static void _OnHasSettingValueChanged(const Windows::UI::Xaml::DependencyObject& d, const Windows::UI::Xaml::DependencyPropertyChangedEventArgs& e);
        //static hstring _GenerateOverrideMessage(const IInspectable& settingOrigin);
        //void _UpdateOverrideSystem();
        winrt::event<winrt::Windows::Foundation::TypedEventHandler<DevStar::ItemContainer, Windows::Foundation::IInspectable>> _ClearSettingValueHandlers;
    };
}

namespace winrt::DevStar::factory_implementation
{
    struct ItemContainer : ItemContainerT<ItemContainer, implementation::ItemContainer>
    {
    };
}
