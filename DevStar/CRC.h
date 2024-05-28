#pragma once

#include "CRC.g.h"
#include "CRCViewModel.h"
#include "Utils.h"

namespace winrt::DevStar::implementation
{
    struct CRC : CRCT<CRC>, ViewModelHelper<CRC>
    {
        CRC();

        WINRT_PROPERTY(DevStar::CRCViewModel, ViewModel,);

    public:
        winrt::hstring CRC_Data() const noexcept;
        void CRC_Data(const winrt::hstring& value);
        void CRC_Data_TextChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::TextChangedEventArgs const& e);
        void CrcStackPanel_Loaded(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);
        void InfoBar_Closed(Microsoft::UI::Xaml::Controls::InfoBar const& sender, Microsoft::UI::Xaml::Controls::InfoBarClosedEventArgs const& args);
        void Show_Warning(const winrt::hstring& w);
        void Update_CRC(std::string& w, winrt::hstring& algo);
        void CRC_SelectionChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void ClearButtonClicked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

    public:
        void InvertUint8(unsigned char* dst, unsigned char* src);
        void InvertUint16(unsigned short* dst, unsigned short* src);
        void InvertUint32(unsigned int* dst, unsigned int* src);
        winrt::hstring crc_4_itu(std::string& w);
        winrt::hstring crc_5_itu(std::string& w);
        winrt::hstring crc_5_epc(std::string& w);
        winrt::hstring crc_5_usb(std::string& w);
        winrt::hstring crc_6_itu(std::string& w);
        winrt::hstring crc_7_mmc(std::string& w);
        winrt::hstring crc_8(std::string& w);
        winrt::hstring crc_8_itu(std::string& w);
        winrt::hstring crc_8_rohc(std::string& w);
        winrt::hstring crc_8_maxim(std::string& w);
        winrt::hstring crc_16_ibm(std::string& w);
        winrt::hstring crc_16_maxim(std::string& w);
        winrt::hstring crc_16_usb(std::string& w);
        winrt::hstring crc_16_modbus(std::string& w);
        winrt::hstring crc_16_ccitt(std::string& w);
        winrt::hstring crc_16_ccitt_false(std::string& w);
        winrt::hstring crc_16_x25(std::string& w);
        winrt::hstring crc_16_xmodem(std::string& w);
        winrt::hstring crc_16_dnp(std::string& w);
        winrt::hstring crc_32(std::string& w);
        winrt::hstring crc_32_mpeg_2(std::string& w);

    private:
        winrt::hstring _crc_data; 
    public:
        void InfoBar_PointerEntered(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Input::PointerRoutedEventArgs const& e);
    };
}

namespace winrt::DevStar::factory_implementation
{
    struct CRC : CRCT<CRC, implementation::CRC>
    {
    };
}
