#pragma once

#include "SpeedViewModel.g.h"
#include "Utils.h"
#include "ViewModelHelpers.h"

namespace winrt::DevStar::implementation
{
    struct SpeedViewModel : SpeedViewModelT<SpeedViewModel>, ViewModelHelper<SpeedViewModel>
    {
        SpeedViewModel();

        GETSET_BINDABLE_ENUM_SETTING(Protocol, Windows::Foundation::Collections::IObservableVector<winrt::hstring>, L"Serial");        
        GETSET_BINDABLE_ENUM_SETTING(SerialSpeed, Windows::Foundation::Collections::IObservableVector<winrt::hstring>, L"Serial_115200");
        GETSET_BINDABLE_ENUM_SETTING(USBSpeed, Windows::Foundation::Collections::IObservableVector<winrt::hstring>, L"USB_5G");
        GETSET_BINDABLE_ENUM_SETTING(EthernetSpeed, Windows::Foundation::Collections::IObservableVector<winrt::hstring>, L"ETH_1000M");
        GETSET_BINDABLE_ENUM_SETTING(WIFISpeed, Windows::Foundation::Collections::IObservableVector<winrt::hstring>, L"WIFI_150M");
        GETSET_BINDABLE_ENUM_SETTING(RS232Speed, Windows::Foundation::Collections::IObservableVector<winrt::hstring>, L"RS232_9600");
        GETSET_BINDABLE_ENUM_SETTING(RS485Speed, Windows::Foundation::Collections::IObservableVector<winrt::hstring>, L"RS485_115200");
        GETSET_BINDABLE_ENUM_SETTING(SPISpeed, Windows::Foundation::Collections::IObservableVector<winrt::hstring>, L"SPI_10M");
        GETSET_BINDABLE_ENUM_SETTING(I2CSpeed, Windows::Foundation::Collections::IObservableVector<winrt::hstring>, L"I2C_100K");
        GETSET_BINDABLE_ENUM_SETTING(CANSpeed, Windows::Foundation::Collections::IObservableVector<winrt::hstring>, L"CAN_160K");
        GETSET_BINDABLE_ENUM_SETTING(BluetoothSpeed, Windows::Foundation::Collections::IObservableVector<winrt::hstring>, L"Blueth_24M");
        GETSET_BINDABLE_ENUM_SETTING(PCIESpeed, Windows::Foundation::Collections::IObservableVector<winrt::hstring>, L"PCIE3_x4_3p938G");
    };
}

namespace winrt::DevStar::factory_implementation
{
    struct SpeedViewModel : SpeedViewModelT<SpeedViewModel, implementation::SpeedViewModel>
    {
    };
}
