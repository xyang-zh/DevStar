#include "pch.h"

#include "MainPage.h"
#include "MainPage.g.cpp"

#include "LibraryResources.h"

namespace winrt
{
    namespace MUX = Microsoft::UI::Xaml;
    namespace WUX = Windows::UI::Xaml;
}

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI;
using namespace Windows::UI::Core;
using namespace Windows::System;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml::Media;


static const std::wstring_view crcTag{ L"CRC_Nav" };
static const std::wstring_view endianTag{ L"Endian_Nav" };
static const std::wstring_view speedTag{ L"Speed_Nav" };
static const std::wstring_view pathTag{ L"Path_Nav" };
static const std::wstring_view memorySpaceTag{ L"MemorySpace_Nav" };
static const std::wstring_view repeatTag{ L"Repeat_Nav" };
static const std::wstring_view accumulateTag{ L"Add_Nav" };
static const std::wstring_view macroTag{ L"Macro_Nav" };
static const std::wstring_view settingsTag{ L"Settings_Nav" };


namespace winrt::DevStar::implementation
{
    MainPage::MainPage()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        InitializeComponent();

        CoreApplicationViewTitleBar coretitlebar = CoreApplication::GetCurrentView().TitleBar();
        coretitlebar.ExtendViewIntoTitleBar(true);

        ApplicationViewTitleBar titlebar = ApplicationView::GetForCurrentView().TitleBar();
        titlebar.ButtonBackgroundColor(Colors::Transparent());

        Window::Current().SetTitleBar(AppTitleBar());

        coretitlebar.LayoutMetricsChanged([=](const CoreApplicationViewTitleBar & /*sender*/, 
                IInspectable const& /*args*/)
        {
            LeftPaddingColumn().Width(GridLength{ coretitlebar.SystemOverlayLeftInset() });
            RightPaddingColumn().Width(GridLength{ coretitlebar.SystemOverlayRightInset() });
        });

        coretitlebar.IsVisibleChanged([=](const CoreApplicationViewTitleBar &sender, 
                IInspectable const& /*args*/)
        {
            if (sender.IsVisible())
            {
                AppTitleBar().Visibility(Visibility::Visible);
            }
            else
            {
                AppTitleBar().Visibility(Visibility::Collapsed);
            }
        });

        Window::Current().CoreWindow().Activated([=](const winrt::Windows::UI::Core::CoreWindow& /*sender*/,
                WindowActivatedEventArgs const& args)
        {
            UISettings settings{ UISettings() };
            
            if (args.WindowActivationState() == CoreWindowActivationState::Deactivated)
            {
                winrt::Windows::UI::Xaml::Media::SolidColorBrush graybrash { 
                                    settings.UIElementColor(UIElementType::GrayText) };
                AppTitleTextBlock().Foreground(graybrash);
            }
            else
            {
                winrt::Windows::UI::Xaml::Media::SolidColorBrush windowbrash { 
                                    settings.UIElementColor(UIElementType::WindowText) };
                AppTitleTextBlock().Foreground(windowbrash);
            }
        });
    }

    void MainPage::SettingsNav_Loaded(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Windows::UI::Xaml::RoutedEventArgs const& /*e*/)
    {
        if (SettingsNav().SelectedItem() == nullptr)
        {
            const auto initialItem = SettingsNav().MenuItems().GetAt(0);

            SettingsNav().SelectedItem(initialItem);

            // Manually navigate because setting the selected item programmatically doesn't trigger ItemInvoked.
            // weird phenomenon.
            if (const auto tag = initialItem.as<Microsoft::UI::Xaml::Controls::NavigationViewItem>().Tag())
            {
                _Navigate(unbox_value<hstring>(tag), L"");
            }
        }
    }

    void MainPage::SettingsNav_ItemInvoked(const MUX::Controls::NavigationView& /*sender*/, const MUX::Controls::NavigationViewItemInvokedEventArgs& args)
    {
        if (const auto clickedItemContainer = args.InvokedItemContainer())
        {
            if (clickedItemContainer.IsSelected())
            {
                // Clicked on the selected item.
                // Don't navigate to the same page again.
                return;
            }

            if (const auto navString = clickedItemContainer.Tag().try_as<hstring>())
            {
                _Navigate(*navString, hstring {});
            }
            //else if (const auto profile = clickedItemContainer.Tag().try_as<Editor::ProfileViewModel>())
            //{
            //    // Navigate to a page with the given profile
            //    _Navigate(profile, BreadcrumbSubPage::None);
            //}
        }
    }

    void MainPage::SettingsNav_DisplayModeChanged(const Microsoft::UI::Xaml::Controls::NavigationView& sender, const Microsoft::UI::Xaml::Controls::NavigationViewDisplayModeChangedEventArgs& /*e*/)
    {                
        ApplicationView view = ApplicationView::GetForCurrentView();

        auto val = view.ViewMode();

        bool isCompactOverlayMode = val == ApplicationViewMode::CompactOverlay;
               
        bool rc = VisualStateManager().GoToState(this->contentFrame(), winrt::hstring{L"NavigationViewCompact"}, true);
        //this->contentFrame().
        auto group = VisualStateManager().GetVisualStateGroups(sender); 
        
        auto ll = StateGroup().CurrentState();


        if (isCompactOverlayMode || rc)
        {
            VisualStateManager().GoToState(this->contentFrame(), winrt::hstring{L"NavigationViewMinimal"}, true);
        }

        //if (isCompactOverlayMode)
        //{
        //    VisualStateManager.GoToState(this, CompactOverlayStateName, useTransitions: true);
        //}
        //else
        //{
        //    switch ((NavigationViewDisplayMode)ViewModel.NavigationViewDisplayMode)
        //    {
        //    case NavigationViewDisplayMode.Minimal:
       
       
                //bool rc = VisualStateManager().GoToState(sender, winrt::hstring{L"NavigationViewMinimal"}, true);
                //if (!rc)
                //{
                //    int d = 10;
                //    //VisualStateGroup().;
                //    //auto cur = VisualStateManager().GetVisualStateGroups()
                //}
        //        break;

        //    case NavigationViewDisplayMode.Compact:
        //        VisualStateManager.GoToState(this, NavigationViewCompactStateName, useTransitions: true);
        //        break;

        //    case NavigationViewDisplayMode.Expanded:
        //        VisualStateManager.GoToState(this, NavigationViewExpandedStateName, useTransitions: true);
        //        break;
        //    }
        //}
    }

    void MainPage::_Navigate(hstring clickedItemTag, hstring /*subPage*/)
    {
        if (clickedItemTag == crcTag)
        {
            contentFrame().Navigate(xaml_typename<DevStar::CRC>());  
            
            SettingsNav().Header(box_value(LocalizedNameForResource(winrt::hstring{ crcTag }, L"Content")));
        }
        else if (clickedItemTag == endianTag)
        {
            contentFrame().Navigate(xaml_typename<DevStar::Endian>());

            SettingsNav().Header(box_value(LocalizedNameForResource(winrt::hstring{ endianTag }, L"Content")));
        }
        else if (clickedItemTag == speedTag)
        {
            contentFrame().Navigate(xaml_typename<DevStar::Speed>());

            SettingsNav().Header(box_value(LocalizedNameForResource(winrt::hstring{ speedTag }, L"Content")));
        }
        else if (clickedItemTag == pathTag)
        {
            contentFrame().Navigate(xaml_typename<DevStar::Path>());

            SettingsNav().Header(box_value(LocalizedNameForResource(winrt::hstring{ pathTag }, L"Content")));
        }
        else if (clickedItemTag == memorySpaceTag)
        {
            contentFrame().Navigate(xaml_typename<DevStar::MemorySpace>());

            SettingsNav().Header(box_value(LocalizedNameForResource(winrt::hstring{ memorySpaceTag }, L"Content")));
        }
        else if (clickedItemTag == repeatTag)
        {
            contentFrame().Navigate(xaml_typename<DevStar::Repeat>());

            SettingsNav().Header(box_value(LocalizedNameForResource(winrt::hstring{ repeatTag }, L"Content")));
        }
        else if (clickedItemTag == accumulateTag)
        {
            contentFrame().Navigate(xaml_typename<DevStar::Accumulate>());

            SettingsNav().Header(box_value(LocalizedNameForResource(winrt::hstring{ accumulateTag }, L"Content")));
        }
        else if (clickedItemTag == macroTag)
        {
            contentFrame().Navigate(xaml_typename<DevStar::Macro>());

            SettingsNav().Header(box_value(LocalizedNameForResource(winrt::hstring{ macroTag }, L"Content")));
        }
        else if (clickedItemTag == settingsTag)
        {
            contentFrame().Navigate(xaml_typename<DevStar::Settings>());

            SettingsNav().Header(box_value(LocalizedNameForResource(winrt::hstring{ settingsTag }, L"Content")));
        }
        else
        {
            return;
        }
    }
}
