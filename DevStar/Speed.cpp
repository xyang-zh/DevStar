#include "pch.h"

#include "Speed.h"
#if __has_include("Speed.g.cpp")
#include "Speed.g.cpp"
#endif

#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>

#include "LibraryResources.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

static const std::wstring_view HighSpeedUnitsTag{ L"mMgG" };
static const std::wstring_view LowSpeedUnitsTag{ L"kK" };
static const std::wstring_view TooHighSpeedTag{ L"注意：速度过高" };
static const std::wstring_view DefaultTimelTag{ L"用时：0s" };
static const std::wstring_view InvalidSpeedUnitTag{ L"注意：单位不支持" };
static const std::wstring_view InvalidProtocolTag{ L"注意：未知协议" };

static const std::wstring_view SerialTag{ L"Serial" };
static const std::wstring_view USBTag{ L"USB" };
static const std::wstring_view EthernetTag{ L"Ethernet" };
static const std::wstring_view WIFITag{ L"WIFI" };
static const std::wstring_view RS232Tag{ L"RS232" };
static const std::wstring_view RS485Tag{ L"RS485" };
static const std::wstring_view SPITag{ L"SPI" };
static const std::wstring_view I2CTag{ L"I2C" };
static const std::wstring_view CANTag{ L"CAN" };
static const std::wstring_view BluetoothTag{ L"Bluetooth" };
static const std::wstring_view PCIETag{ L"PCIE" };
static const std::wstring_view ProtocolTag{ L"Protocol" };
static const std::wstring_view SendBoxTag{ L"SendBox" };

namespace winrt::DevStar::implementation
{
	Speed::Speed()
	{
	}

    void Speed::SpeedPanelLoaded(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::RoutedEventArgs const& /*e*/)
    {
        //if (SerialSpeed Binarys().SelectedItem() == nullptr)
        //{
        //    const auto initliaItem = Binarys().Items().GetAt(0);

        //    Binarys().SelectedItem(initliaItem);
        //}
    }

    void Speed::ClearButtonClicked(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Windows::UI::Xaml::RoutedEventArgs const& /*e*/)
    {
        SendBox().Text(L"");
    }

	void Speed::ProtocolChanged(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& /*e*/)
	{
        winrt::hstring source{ ProtocolTag };

        NotifyChanged(source);
	}
    
    void Speed::SerialSpeedChanged(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& /*e*/)
    {
        winrt::hstring source{ SerialTag };

        NotifyChanged(source);
    }

    void Speed::USBSpeedChanged(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& /*e*/)
    {
        winrt::hstring source{ USBTag };

        NotifyChanged(source);
    }

    void Speed::EthernetSpeedChanged(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& /*e*/)
    {
        winrt::hstring source{ EthernetTag };

        NotifyChanged(source);
    }

    void Speed::WIFISpeedChanged(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& /*e*/)
    {
        winrt::hstring source{ WIFITag };

        NotifyChanged(source);
    }

    void Speed::RS232SpeedChanged(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& /*e*/)
    {
        winrt::hstring source{ RS232Tag };

        NotifyChanged(source);
    }

    void Speed::RS485SpeedChanged(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& /*e*/)
    {
        winrt::hstring source{ RS485Tag };

        NotifyChanged(source);
    }

    void Speed::SPISpeedChanged(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& /*e*/)
    {
        winrt::hstring source{ SPITag };

        NotifyChanged(source);
    }

    void Speed::I2CSpeedChanged(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& /*e*/)
    {
        winrt::hstring source{ I2CTag };

        NotifyChanged(source);
    }

    void Speed::CANSpeedChanged(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& /*e*/)
    {
        winrt::hstring source{ CANTag };

        NotifyChanged(source);
    }

    void Speed::BluetoothSpeedChanged(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& /*e*/)
    {
        winrt::hstring source{ BluetoothTag };

        NotifyChanged(source);
    }

    void Speed::PCIESpeedChanged(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& /*e*/)
    {
        winrt::hstring source{ PCIETag };

        NotifyChanged(source);
    }

    void Speed::SendTextChanged(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::Controls::TextChangedEventArgs const& /*e*/)
    {
        winrt::hstring source{ SendBoxTag };

        NotifyChanged(source);
    }

    void Speed::RefreshTimeUse(winrt::hstring& _speed, uint32_t textsize)
    {
        double          speed{ 0 }, timePerBit;
        double          usetime_s, usetime_ns, usetime_us, usetime_ms;
        uint32_t        bits;
        std::string     uint{ "1" };
        winrt::hstring  UseTime{ L"" };
        std::vector<std::string> speedList;

        if (_speed.empty() || textsize == 0)
        { 
            TimeUse().Text(DefaultTimelTag);
            return;
        }

        boost::split(speedList, winrt::to_string(_speed), boost::is_any_of(" "), boost::token_compress_on);

        if (speedList.size() > 1 && boost::contains(HighSpeedUnitsTag, speedList[1]))
        {
            TimeUse().Text(TooHighSpeedTag);
            return;
        }
        else if (speedList.size() > 1 && !boost::contains(LowSpeedUnitsTag, speedList[1]))
        {
            TimeUse().Text(InvalidSpeedUnitTag);
            return;
        }
        else if (speedList.size() > 1)
        {
            uint = "1000";
        }

        try
        {
            speed = std::stod(speedList[0]);
        }
        CATCH_LOG();

        speed = uint == "1000" ? speed * 1000 : speed;

        timePerBit = (double)(1.0 / speed);
        bits = textsize * 8;
        usetime_s = timePerBit * bits;
        usetime_ms = usetime_s * 1000;
        usetime_us = usetime_s * 1000000;
        usetime_ns = usetime_s * 1000000000;

        if (usetime_s >= 1.0)
        {
            UseTime = winrt::hstring{ L"用时：" } + winrt::to_hstring((boost::format("%.3f s") % usetime_s).str());
        }
        else if (usetime_ms >= 1.0)
        {
            UseTime = winrt::hstring{ L"用时：" } + winrt::to_hstring((boost::format("%.3f ms") % usetime_ms).str());
        }
        else if (usetime_us >= 1.0)
        {
            UseTime = winrt::hstring{ L"用时：" } + winrt::to_hstring((boost::format("%.3f us") % usetime_us).str());
        }
        else
        {
            UseTime = winrt::hstring{ L"用时：" } + winrt::to_hstring((boost::format("%.3f ns") % usetime_ns).str());
        }
        TimeUse().Text(UseTime);
    }

    void Speed::NotifyChanged(winrt::hstring& args)
    {
        auto protocol{ winrt::unbox_value<hstring>(ViewModel().CurrentProtocol()) };
        winrt::hstring speed{ L"" };

        if (args != RS_(ProtocolTag) && args != RS_(SendBoxTag) && RS(args) != protocol)
        { 
            return;
        }

        if (protocol == RS_(SerialTag))
        {
            speed = winrt::unbox_value<winrt::hstring>(ViewModel().CurrentSerialSpeed());
        }
        else if (protocol == RS_(USBTag))
        {
            speed = winrt::unbox_value<winrt::hstring>(ViewModel().CurrentUSBSpeed());
        }
        else if (protocol == RS_(EthernetTag))
        {
            speed = winrt::unbox_value<winrt::hstring>(ViewModel().CurrentEthernetSpeed());
        }
        else if (protocol == RS_(WIFITag))
        {
            speed = winrt::unbox_value<winrt::hstring>(ViewModel().CurrentWIFISpeed());
        }
        else if (protocol == RS_(RS232Tag))
        {
            speed = winrt::unbox_value<winrt::hstring>(ViewModel().CurrentRS232Speed());
        }
        else if (protocol == RS_(RS485Tag))
        {
            speed = winrt::unbox_value<winrt::hstring>(ViewModel().CurrentRS485Speed());
        }
        else if (protocol == RS_(SPITag))
        {
            speed = winrt::unbox_value<winrt::hstring>(ViewModel().CurrentSPISpeed());
        }
        else if (protocol == RS_(I2CTag))
        {
            speed = winrt::unbox_value<winrt::hstring>(ViewModel().CurrentI2CSpeed());
        }
        else if (protocol == RS_(CANTag))
        {
            speed = winrt::unbox_value<winrt::hstring>(ViewModel().CurrentCANSpeed());
        }
        else if (protocol == RS_(BluetoothTag))
        {
            speed = winrt::unbox_value<winrt::hstring>(ViewModel().CurrentBluetoothSpeed());
        }
        else if (protocol == RS_(PCIETag))
        {
            speed = winrt::unbox_value<winrt::hstring>(ViewModel().CurrentPCIESpeed());
        }
        else
        {
            TimeUse().Text(InvalidProtocolTag);
            return;
        }

        RefreshTimeUse(speed, SendBox().Text().size());
    }
}
