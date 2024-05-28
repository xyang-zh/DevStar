#pragma once

#include "Speed.g.h"
#include "SpeedViewModel.h"

namespace winrt::DevStar::implementation
{
    struct Speed : SpeedT<Speed>
    {
        Speed();
        WINRT_PROPERTY(DevStar::SpeedViewModel, ViewModel, );

    public:
        void ProtocolChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);        
        void SerialSpeedChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void USBSpeedChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void EthernetSpeedChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void WIFISpeedChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);        
        void RS232SpeedChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void RS485SpeedChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void SPISpeedChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void I2CSpeedChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void CANSpeedChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void PCIESpeedChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void BluetoothSpeedChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);

        void SpeedPanelLoaded(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);
        void SendTextChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::TextChangedEventArgs const& e);
        void RefreshTimeUse(winrt::hstring& _speed, uint32_t textsize);
        void NotifyChanged(winrt::hstring& args);
        void ClearButtonClicked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::DevStar::factory_implementation
{
    struct Speed : SpeedT<Speed, implementation::Speed>
    {
    };
}
