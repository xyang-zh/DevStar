#include "pch.h"

#include "CRC.h"
#if __has_include("CRC.g.cpp")
#include "CRC.g.cpp"
#endif

#include <CRCViewModel.h>
#include <boost/format.hpp>
#include <algorithm>

using namespace std;
using namespace winrt;
using namespace Windows::UI::Xaml;

static const std::wstring_view  crc_4_itu_Tag{ L"CRC-4 (ITU)" };
static const std::wstring_view  crc_5_itu_Tag{ L"CRC-5 (ITU)" };
static const std::wstring_view  crc_5_epc_Tag{ L"CRC-5 (EPC)" };
static const std::wstring_view  crc_5_usb_Tag{ L"CRC-5 (USB)" };
static const std::wstring_view  crc_6_itu_Tag{ L"CRC-6 (ITU)" };
static const std::wstring_view  crc_7_mmc_Tag{ L"CRC-7 (MMC)" };
static const std::wstring_view  crc_8_Tag{ L"CRC-8" };
static const std::wstring_view  crc_8_itu_Tag{ L"CRC-8 (ITU)" };
static const std::wstring_view  crc_8_rohc_Tag{ L"CRC-8 (ROHC)" };
static const std::wstring_view  crc_8_maxim_Tag{ L"CRC-8 (MAXIM)" };
static const std::wstring_view  crc_16_ibm_Tag{ L"CRC-16 (IBM)" };
static const std::wstring_view  crc_16_modbus_Tag{ L"CRC-16 (MODBUS)" };
static const std::wstring_view  crc_16_ccitt_Tag{ L"CRC-16 (CCITT)" };
static const std::wstring_view  crc_16_ccitt_false_Tag{ L"CRC-16 (CCITT-FALSE)" };
static const std::wstring_view  crc_16_x25_Tag{ L"CRC-16 (X25)" };
static const std::wstring_view  crc_16_xmodem_Tag{ L"CRC-16 (XMODEM)" };
static const std::wstring_view  crc_16_dnp_Tag{ L"CRC-16 (DNP)" };
static const std::wstring_view  crc_32_Tag{ L"CRC-32" };
static const std::wstring_view  crc_32_mpeg_2_Tag{ L"CRC-32 (MPEG-2)" };


namespace winrt::DevStar::implementation
{
	CRC::CRC()
	{
        PropertyChanged([this](auto&&, const PropertyChangedEventArgs& /*args*/) {
            //const auto viewModelProperty{ args.PropertyName() };
            // if (viewModelProperty == L"StartingDirectory")
            //{
            //    // notify listener that all starting directory related values might have changed
            //    // NOTE: this is similar to what is done with BackgroundImagePath above
            //    _NotifyChanges(L"UseParentProcessDirectory", L"UseCustomStartingDirectory");
            //}           
            });
	}

    void CRC::CrcStackPanel_Loaded(winrt::Windows::Foundation::IInspectable const& /*sender*/, 
                                   winrt::Windows::UI::Xaml::RoutedEventArgs const& /*e*/)
    {
        InfoBar().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
    }

	winrt::hstring CRC::CRC_Data() const noexcept
	{
		return L"";
	}
	
	void CRC::CRC_Data(const winrt::hstring& value)
	{
		_crc_data = value;
	}

	void CRC::CRC_Data_TextChanged(winrt::Windows::Foundation::IInspectable const& /*sender*/,
					    winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& /*e*/)
	{
        winrt::hstring current{ winrt::unbox_value<hstring>(_ViewModel.CurrentCRC()) };
        std::string raw_text{ winrt::to_string(Target().Text()) };
        bool is_number{ false };

        if (raw_text.size() == 0)
        {
            InfoBar().IsOpen(false);
            return;
        }
        else
        {
            try
            {
                is_number = raw_text.find_first_not_of("0123456789abcdefABCDEF") == std::string::npos;
            }
            CATCH_LOG();
        }

        if (!is_number)
        {
            Show_Warning(L"当前输入的内容包含无效的 十六进制");
            return;
        }
        else
        {
            InfoBar().IsOpen(false);
        }

        Update_CRC(raw_text, current);
	}

    void CRC::Update_CRC(std::string& w, winrt::hstring& algo)
    {
        winrt::hstring crc;

        if (!w.size())
        { 
            return Crc().Text(L"");            
        }

        if (algo == crc_4_itu_Tag)
        {
            crc = crc_4_itu(w);
        }
        else if (algo == crc_5_itu_Tag)
        {
            crc = crc_5_itu(w);
        }
        else if (algo == crc_5_epc_Tag)
        {
            crc = crc_5_epc(w);
        }
        else if (algo == crc_5_usb_Tag)
        {
            crc = crc_5_usb(w);
        }
        else if (algo == crc_6_itu_Tag)
        {
            crc = crc_6_itu(w);
        }
        else if (algo == crc_7_mmc_Tag)
        {
            crc = crc_7_mmc(w);
        }
        else if (algo == crc_8_Tag)
        {
            crc = crc_8(w);
        }
        else if (algo == crc_8_itu_Tag)
        {
            crc = crc_8_itu(w);
        }
        else if (algo == crc_8_rohc_Tag)
        {
            crc = crc_8_rohc(w);
        }
        else if (algo == crc_8_maxim_Tag)
        {
            crc = crc_8_maxim(w);
        }
        else if (algo == crc_16_ibm_Tag)
        {
            crc = crc_16_ibm(w);
        }
        else if (algo == crc_16_modbus_Tag)
        {
            crc = crc_16_modbus(w);
        }
        else if (algo == crc_16_ccitt_Tag)
        {
            crc = crc_16_ccitt(w);
        }
        else if (algo == crc_16_ccitt_false_Tag)
        {
            crc = crc_16_ccitt_false(w);
        }
        else if (algo == crc_16_x25_Tag)
        {
            crc = crc_16_x25(w);
        }
        else if (algo == crc_16_xmodem_Tag)
        {
            crc = crc_16_xmodem(w);
        }
        else if (algo == crc_16_dnp_Tag)
        {
            crc = crc_16_dnp(w);
        }
        else if (algo == crc_32_Tag)
        {
            crc = crc_32(w);
        }
        else if (algo == crc_32_mpeg_2_Tag)
        {
            crc = crc_32_mpeg_2(w);
        }
        
        Crc().Text(crc);      
    }

    void CRC::InfoBar_Closed(winrt::Microsoft::UI::Xaml::Controls::InfoBar const& /*sender*/,
                             winrt::Microsoft::UI::Xaml::Controls::InfoBarClosedEventArgs const& /*args*/)
    {
        InfoBar().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
    }

    void CRC::Show_Warning(const winrt::hstring& w)
    {
        if (InfoBar().IsOpen()) { return; }

        InfoBar().Visibility(Windows::UI::Xaml::Visibility::Visible);
        InfoBar().Message(w);
        InfoBar().IsOpen(true);
    }

    void CRC::ClearButtonClicked(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Windows::UI::Xaml::RoutedEventArgs const& /*e*/)
    {
        Target().Text(L"");
        Crc().Text(L"");
    }

    void CRC::CRC_SelectionChanged(Windows::Foundation::IInspectable const& /*sender*/,
                                   Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& /*e*/)
    {
        winrt::hstring current{ winrt::unbox_value<winrt::hstring>(_ViewModel.CurrentCRC()) };
        std::string raw_Text{ winrt::to_string(Target().Text()) };

        Update_CRC(raw_Text, current);
    }

    void CRC::InvertUint8(unsigned char* dst, unsigned char* src)
    {
        int i;
        unsigned char t[4] = { 0 };

        for (i = 0; i < 8; i++)
        {
            if (src[0] & (1 << i))
            {
                t[0] |= 1 << (7 - i);
            }
        }
        dst[0] = t[0];
    }

    void CRC::InvertUint16(unsigned short* dst, unsigned short* src)
    {
        int i;
        unsigned short t[4] = { 0 };

        for (i = 0; i < 16; i++)
        {
            if (src[0] & (1 << i))
            {
                t[0] |= 1 << (15 - i);
            }
        }
        dst[0] = t[0];
    }

    void CRC::InvertUint32(unsigned int* dst, unsigned int* src)
    {
        int i;
        unsigned char t[4] = { 0 };

        for (i = 0; i < 32; i++)
        {
            if (src[0] & (1 << i))
            {
                t[0] |= 1 << (31 - i);
            }
        }
        dst[0] = t[0];
    }

    winrt::hstring CRC::crc_4_itu(std::string& w)
    {
        unsigned char CRCin = 0x00;
        unsigned char CPoly = 0x03;
        unsigned char c = 0;
        hstring     crc_hex;
        const char* p = w.c_str();
        size_t      len = w.size();

        while (len--)
        {
            c = *(p++);
            InvertUint8(&c, &c);
            CRCin ^= c;
            for (size_t i = 0; i < 8; i++)
            {
                if (CRCin & 0x80)
                {
                    CRCin = (CRCin << 1) ^ (CPoly << 4);
                }
                else
                {
                    CRCin = CRCin << 1;
                }
            }
        }
        InvertUint8(&CRCin, &CRCin);

        crc_hex = winrt::to_hstring((boost::format("%x") % (unsigned short)CRCin).str());

        return  crc_hex;
    }

    winrt::hstring CRC::crc_5_itu(std::string& w)
    {
        unsigned char CRCin = 0x00;
        unsigned char CPoly = 0x15;
        hstring     crc_hex;
        const char* p = w.c_str();
        size_t      len = w.size();

        InvertUint8(&CPoly, &CPoly);
        while (len--)
        {
            CRCin ^= *(p++);            
            for (size_t i = 0; i < 8; i++)
            {
                if (CRCin & 0x01)
                {
                    CRCin = (CRCin >> 1) ^ (CPoly >> 3);
                }
                else
                {
                    CRCin = CRCin >> 1;
                }
            }
        }

        crc_hex = winrt::to_hstring((boost::format("%x") % (unsigned short)CRCin).str());

        return  crc_hex;
    }

    winrt::hstring CRC::crc_5_epc(std::string& w)
    {
        unsigned char CRCin = 0x00;
        unsigned char CPoly = 0x48;
        hstring     crc_hex;
        const char* p = w.c_str();
        size_t      len = w.size();

        while (len--)
        {
            CRCin ^= *(p++);
            for (size_t i = 0; i < 8; i++)
            {
                if (CRCin & 0x80)
                {
                    CRCin = (CRCin << 1) ^ CPoly;
                }
                else
                {
                    CRCin = CRCin << 1;
                }
            }
        }
        CRCin = CRCin >> 3;

        crc_hex = winrt::to_hstring((boost::format("%x") % (unsigned short)CRCin).str());

        return  crc_hex;
    }

    winrt::hstring CRC::crc_5_usb(std::string& w)
    {
        unsigned char CRCin = 0x1F;
        unsigned char CPoly = 0x14;
        hstring     crc_hex;
        const char* p = w.c_str();
        size_t      len = w.size();

        while (len--)
        {
            CRCin ^= *(p++);
            for (size_t i = 0; i < 8; i++)
            {
                if (CRCin & 0x01)
                {
                    CRCin = (CRCin >> 1) ^ CPoly;
                }
                else
                {
                    CRCin = CRCin >> 1;
                }
            }
        }
        CRCin ^= CRCin;

        crc_hex = winrt::to_hstring((boost::format("%x") % (unsigned short)CRCin).str());

        return  crc_hex;
    }

    winrt::hstring CRC::crc_6_itu(std::string& w)
    {
        unsigned char CRCin = 0x00;
        unsigned char CPoly = 0x03;
        unsigned char c = 0;
        hstring     crc_hex;
        const char* p = w.c_str();
        size_t      len = w.size();

        while (len--)
        {
            c = *(p++);
            InvertUint8(&c, &c);
            CRCin ^= c;
            for (size_t i = 0; i < 8; i++)
            {
                if (CRCin & 0x80)
                {
                    CRCin = (CRCin << 1) ^ (CPoly << 2);
                }
                else
                {
                    CRCin = CRCin << 1;
                }
            }
        }
        InvertUint8(&CRCin, &CRCin);

        crc_hex = winrt::to_hstring((boost::format("%x") % (unsigned short)CRCin).str());

        return  crc_hex;
    }

    winrt::hstring CRC::crc_7_mmc(std::string& w)
    {
        unsigned char CRCin = 0x00;
        unsigned char CPoly = 0x09;
        hstring     crc_hex;
        const char* p = w.c_str();
        size_t      len = w.size();

        while (len--)
        {
            CRCin ^= *(p++);            
            for (size_t i = 0; i < 8; i++)
            {
                if (CRCin & 0x80)
                {
                    CRCin = (CRCin << 1) ^ (CPoly << 1);
                }
                else
                {
                    CRCin = CRCin << 1;
                }
            }
        }
        
        CRCin >>= 1;
        crc_hex = winrt::to_hstring((boost::format("%x") % (unsigned short)CRCin).str());

        return  crc_hex;
    }

    winrt::hstring CRC::crc_8(std::string& w)
    {
        unsigned char CRCin = 0x00;
        unsigned char CPoly = 0x07;
        hstring     crc_hex;
        const char* p = w.c_str();
        size_t      len = w.size();

        while (len--)
        {
            CRCin ^= *(p++);
            for (size_t i = 0; i < 8; i++)
            {
                if (CRCin & 0x80)
                {
                    CRCin = (CRCin << 1) ^ CPoly;
                }
                else
                {
                    CRCin = CRCin << 1;
                }
            }
        }
        
        crc_hex = winrt::to_hstring((boost::format("%x") % (unsigned short)CRCin).str());

        return  crc_hex;
    }

    winrt::hstring CRC::crc_8_itu(std::string& w)
    {
        unsigned char CRCin = 0x00;
        unsigned char CPoly = 0x07;
        hstring     crc_hex;
        const char* p = w.c_str();
        size_t      len = w.size();

        while (len--)
        {
            CRCin ^= *(p++);
            for (size_t i = 0; i < 8; i++)
            {
                if (CRCin & 0x80)
                {
                    CRCin = (CRCin << 1) ^ CPoly;
                }
                else
                {
                    CRCin = CRCin << 1;
                }
            }
        }

        CRCin ^= 0x55;
        crc_hex = winrt::to_hstring((boost::format("%x") % (unsigned short)CRCin).str());

        return  crc_hex;
    }

    winrt::hstring CRC::crc_8_rohc(std::string& w)
    {
        unsigned char CRCin = 0xFF;
        unsigned char CPoly = 0x07;
        hstring     crc_hex;
        const char* p = w.c_str();
        size_t      len = w.size();

        InvertUint8(&CPoly, &CPoly);
        while (len--)
        {
            CRCin ^= *(p++);
            for (size_t i = 0; i < 8; i++)
            {
                if (CRCin & 0x01)
                {
                    CRCin = (CRCin >> 1) ^ CPoly;
                }
                else
                {
                    CRCin = CRCin >> 1;
                }
            }
        }

        crc_hex = winrt::to_hstring((boost::format("%x") % (unsigned short)CRCin).str());

        return  crc_hex;
    }

    winrt::hstring CRC::crc_8_maxim(std::string& w)
    {
        unsigned char CRCin = 0x00;
        unsigned char CPoly = 0x31;
        hstring     crc_hex;
        const char* p = w.c_str();
        size_t      len = w.size();

        InvertUint8(&CPoly, &CPoly);
        while (len--)
        {
            CRCin ^= *(p++);
            for (size_t i = 0; i < 8; i++)
            {
                if (CRCin & 0x01)
                {
                    CRCin = (CRCin >> 1) ^ CPoly;
                }
                else
                {
                    CRCin = CRCin >> 1;
                }
            }
        }

        crc_hex = winrt::to_hstring((boost::format("%x") % (unsigned short)CRCin).str());

        return  crc_hex;
    }

    winrt::hstring CRC::crc_16_ibm(std::string& w)
    {
        unsigned short CRCin = 0x0000;
        unsigned short CPoly = 0x8005;
        hstring     crc_hex;
        const char* p = w.c_str();
        size_t      len  = w.size();
        
        while (len--)
        {
            CRCin ^= *(p++);
            for (size_t i = 0; i < 8; i++)
            {
                if (CRCin & 0x01)
                {
                    CRCin = (CRCin >> 1) ^ CPoly;
                }
                else
                {
                    CRCin = CRCin >> 1;
                }
            }
        }
        InvertUint16(&CRCin, &CRCin);

        crc_hex = winrt::to_hstring((boost::format("%x") % CRCin).str());

        return  crc_hex;
    }

    winrt::hstring CRC::crc_16_maxim(std::string& w)
    {
        unsigned short CRCin = 0x0000;
        unsigned short CPoly = 0x8005;
        hstring     crc_hex;
        const char* p = w.c_str();
        size_t      len = w.size();

        InvertUint16(&CPoly, &CPoly);
        while (len--)
        {
            CRCin ^= *(p++);
            for (size_t i = 0; i < 8; i++)
            {
                if (CRCin & 0x01)
                {
                    CRCin = (CRCin >> 1) ^ CPoly;
                }
                else
                {
                    CRCin = CRCin >> 1;
                }
            }
        }
        InvertUint16(&CRCin, &CRCin);

        CRCin ^= 0xFFFF;
        crc_hex = winrt::to_hstring((boost::format("%x") % CRCin).str());

        return  crc_hex;
    }

    winrt::hstring CRC::crc_16_usb(std::string& w)
    {
        unsigned short CRCin = 0xFFFF;
        unsigned short CPoly = 0x8005;
        hstring     crc_hex;
        const char* p = w.c_str();
        size_t      len = w.size();

        InvertUint16(&CPoly, &CPoly);
        while (len--)
        {
            CRCin ^= *(p++);
            for (size_t i = 0; i < 8; i++)
            {
                if (CRCin & 0x01)
                {
                    CRCin = (CRCin >> 1) ^ CPoly;
                }
                else
                {
                    CRCin = CRCin >> 1;
                }
            }
        }
        InvertUint16(&CRCin, &CRCin);

        CRCin ^= 0xFFFF;
        crc_hex = winrt::to_hstring((boost::format("%x") % CRCin).str());

        return  crc_hex;
    }

    winrt::hstring CRC::crc_16_modbus(std::string& w)
    {
        unsigned short CRCin = 0xFFFF;
        unsigned short CPoly = 0x8005;
        hstring     crc_hex;
        const char* p = w.c_str();
        size_t      len = w.size();

        InvertUint16(&CPoly, &CPoly);
        while (len--)
        {
            CRCin ^= *(p++);
            for (size_t i = 0; i < 8; i++)
            {
                if (CRCin & 0x01)
                {
                    CRCin = (CRCin >> 1) ^ CPoly;
                }
                else
                {
                    CRCin = CRCin >> 1;
                }
            }
        }

        crc_hex = winrt::to_hstring((boost::format("%x") % CRCin).str());

        return  crc_hex;
    }

    winrt::hstring CRC::crc_16_ccitt(std::string& w)
    {
        unsigned short CRCin = 0xFFFF;
        unsigned short CPoly = 0x1021;
        hstring     crc_hex;
        const char* p = w.c_str();
        size_t      len = w.size();

        InvertUint16(&CPoly, &CPoly);
        while (len--)
        {
            CRCin ^= *(p++);
            for (size_t i = 0; i < 8; i++)
            {
                if (CRCin & 0x01)
                {
                    CRCin = (CRCin >> 1) ^ CPoly;
                }
                else
                {
                    CRCin = CRCin >> 1;
                }
            }
        }

        crc_hex = winrt::to_hstring((boost::format("%x") % CRCin).str());

        return  crc_hex;
    }

    winrt::hstring CRC::crc_16_ccitt_false(std::string& w)
    {
        unsigned short CRCin = 0xFFFF;
        unsigned short CPoly = 0x1021;
        hstring     crc_hex;
        const char* p = w.c_str();
        size_t      len = w.size();

        while (len--)
        {
            CRCin ^= *(p++) << 8;
            for (size_t i = 0; i < 8; i++)
            {
                if (CRCin & 0x8000)
                {
                    CRCin = (CRCin << 1) ^ CPoly;
                }
                else
                {
                    CRCin = CRCin << 1;
                }
            }
        }

        crc_hex = winrt::to_hstring((boost::format("%x") % CRCin).str());

        return  crc_hex;
    }

    winrt::hstring CRC::crc_16_x25(std::string& w)
    {
        unsigned short CRCin = 0xFFFF;
        unsigned short CPoly = 0x8408;
        hstring     crc_hex;
        const char* p = w.c_str();
        size_t      len = w.size();

        while (len--)
        {
            CRCin ^= *(p++);
            for (size_t i = 0; i < 8; i++)
            {
                if (CRCin & 0x0001)
                {
                    CRCin = (CRCin >> 1) ^ CPoly;
                }
                else
                {
                    CRCin = CRCin >> 1;
                }
            }
        }
        CRCin = ~CRCin;

        crc_hex = winrt::to_hstring((boost::format("%x") % CRCin).str());

        return  crc_hex;
    }

    winrt::hstring CRC::crc_16_xmodem(std::string& w)
    {
        unsigned short CRCin = 0x0000;
        unsigned short CPoly = 0x1021;
        hstring     crc_hex;
        const char* p = w.c_str();
        size_t      len = w.size();

        while (len--)
        {
            CRCin ^= *(p++) << 8;
            for (size_t i = 0; i < 8; i++)
            {
                if (CRCin & 0x8000)
                {
                    CRCin = (CRCin << 1) ^ CPoly;
                }
                else
                {
                    CRCin = CRCin << 1;
                }
            }
        }

        crc_hex = winrt::to_hstring((boost::format("%x") % CRCin).str());

        return  crc_hex;
    }

    winrt::hstring CRC::crc_16_dnp(std::string& w)
    {
        unsigned short CRCin = 0x0000;
        unsigned short CPoly = 0x3D65;
        hstring     crc_hex;
        const char* p = w.c_str();
        size_t      len = w.size();

        InvertUint16(&CPoly, &CPoly);
        while (len--)
        {
            CRCin ^= *(p++);
            for (size_t i = 0; i < 8; i++)
            {
                if (CRCin & 0x01)
                {
                    CRCin = (CRCin >> 1) ^ CPoly;
                }
                else
                {
                    CRCin = CRCin >> 1;
                }
            }
        }

        CRCin ^= 0xFFFF;
        crc_hex = winrt::to_hstring((boost::format("%x") % CRCin).str());

        return  crc_hex;
    }

    winrt::hstring CRC::crc_32(std::string& w)
    {
        unsigned int CRCin = 0xFFFFFFFF;
        unsigned int CPoly = 0x04C11DB7;
        hstring     crc_hex;
        const char* p = w.c_str();
        size_t      len = w.size();

        InvertUint32(&CPoly, &CPoly);
        while (len--)
        {
            CRCin ^= *(p++);
            for (size_t i = 0; i < 8; i++)
            {
                if (CRCin & 0x01)
                {
                    CRCin = (CRCin >> 1) ^ CPoly;
                }
                else
                {
                    CRCin = CRCin >> 1;
                }
            }
        }

        CRCin ^= 0xFFFFFFFF;
        crc_hex = winrt::to_hstring((boost::format("%x") % CRCin).str());
        
        return crc_hex;
    }

    winrt::hstring CRC::crc_32_mpeg_2(std::string& w)
    {
        unsigned int CRCin = 0xFFFFFFFF;
        unsigned int CPoly = 0x04C11DB7;
        hstring     crc_hex;
        unsigned char c = 0;
        const char* p = w.c_str();
        size_t      len = w.size();

        while (len--)
        {
            c = *(p++);
            CRCin ^= (c << 24);
            for (size_t i = 0; i < 8; i++)
            {
                if (CRCin & 0x80000000)
                {
                    CRCin = (CRCin << 1) ^ CPoly;
                }
                else
                {
                    CRCin = CRCin << 1;
                }
            }
        }

        crc_hex = winrt::to_hstring((boost::format("%x") % CRCin).str());

        return crc_hex;
    }
}
