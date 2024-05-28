#include "pch.h"

#include "Endian.h"
#if __has_include("Endian.g.cpp")
#include "Endian.g.cpp"
#endif

#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "EndianViewModel.h"
#include "LibraryResources.h"
#include "FallSerializationHelpers.h"

using namespace std;
using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::Foundation::Collections;

static const std::wstring_view hexTag{ L"16进制" };
static const std::wstring_view decTag{ L"10进制" };
static const std::wstring_view width16Tag{ L"16" };
static const std::wstring_view width32Tag{ L"32" };
static const std::wstring_view width64Tag{ L"64" };
static const std::wstring_view TagOnlyTag{ L"TagOnly" };
static const std::wstring_view ExcludeResultTag{ L"ExcludeResult" };
static const std::wstring_view hexContTag{ L"0" };
static const std::wstring_view decContTag{ L"0" };
static const std::wstring_view rowbitsTag{ L"0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000" };
static const std::wstring_view reversebitsTag{ L"0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000" };

namespace winrt::DevStar::implementation
{
    Endian::Endian()
    {
    }

    void Endian::EndiansPanel_Loaded(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::RoutedEventArgs const& /*e*/)
    {
        InfoBar().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
    }

    void Endian::BinarysList_Loaded(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Windows::UI::Xaml::RoutedEventArgs const& /*e*/)
    {
        if (Binarys().SelectedItem() == nullptr)
        {
            const auto initliaItem = Binarys().Items().GetAt(0);
            Binarys().SelectedItem(initliaItem);
        }
    }

    void Endian::DataWidth_Changed(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& /*e*/)
    {
        if (!IsContentValid())
        {
            return;
        }

        EndianConvert();
    }

    void Endian::EndianContents_Changed(Windows::Foundation::IInspectable const& /*sender*/, Windows::UI::Xaml::Controls::TextChangedEventArgs const& /*e*/)
    {
        if (!IsContentValid())
        { 
            return;
        }
        
        EndianConvert();
    }

    void Endian::ClearButtonClicked(winrt::Windows::Foundation::IInspectable const& /*sender*/, winrt::Windows::UI::Xaml::RoutedEventArgs const& /*e*/)
    {
        EndianText().Text(L"");
        EndianReverse().Text(L"");
        EndianConvert();
    }

    void Endian::Show_Warning(const winrt::hstring& w)
    {
        if (InfoBar().IsOpen()) 
        { 
            return;
        }

        InfoBar().Message(w);
        InfoBar().Visibility(Windows::UI::Xaml::Visibility::Visible);
        InfoBar().IsOpen(true);
    }

    void Endian::Close_Warning(void)
    {
        InfoBar().Visibility(Windows::UI::Xaml::Visibility::Collapsed);
        InfoBar().IsOpen(false);
    }

    uint64_t Endian::AtoB64(uint64_t a)
    {
        uint64_t b{ 0ULL };
        uint16_t i{ 0 };

        for (i = 0; i < 8; i++)
        {
            b |= ((a & ((uint64_t)0xFF << (i * 8))) >> (i * 8)) << (56 - i * 8) ;
        }

        return b;
    }

    uint32_t Endian::AtoB32(uint32_t a)
    {
        uint32_t b{ 0ULL };
        uint16_t i{ 0 };

        for (i = 0; i < 4; i++)
        {
            b |= ((a & ((uint32_t)0xFF << (i * 8))) >> (i * 8)) << (24 - i * 8);
        }

        return b;
    }

    uint16_t Endian::AtoB16(uint16_t a)
    {
        return ((a & 0xFF) << 8) | ((a & 0xFF00) >> 8);
    }

    std::vector<winrt::hstring> Endian::BinaryFilter(void)
    {
        winrt::hstring filter;
        std::vector<winrt::hstring> binarys;

        for (const auto& binary : ViewModel().BinaryList())
        {            
            filter = binary.Binary();
            binarys.emplace_back(filter);            
        }

        filter = ViewModel().CurrentBinary().Binary();
        binarys.emplace_back(filter);

        return binarys;
    }

    bool Endian::IsContentValid(void)
    {
        auto width = unbox_value<hstring>(ViewModel().CurrentDataWidths());
        winrt::hstring number_tag{ ViewModel().CurrentBinary().Binary() };
        std::vector<std::string> container;
        bool number{ true };

        boost::split(container, winrt::to_string(EndianText().Text()), boost::is_any_of(" "));
        for (const auto& text : container)
        {
            if (number_tag == hexTag)
            {
                try
                {
                    number = text.find_first_not_of("0123456789abcdefABCDEF ") == std::string::npos;
                    if (!number) { break; }
                }
                CATCH_LOG();
            }
            else if (number_tag == decTag)
            {
                try
                {
                    number = text.find_first_not_of("0123456789 ") == std::string::npos;
                    if (!number) { break; }
                }
                CATCH_LOG();
            }
            else
            {
                Show_Warning(L"未知的 进制");
                return false;
            }

            if (width == width16Tag)
            {
                if (text.length() > 4) { return false; }
            }
            else if (width == width32Tag)
            {
                if (text.length() > 8) { return false; }
            }
            else if (width == width64Tag)
            {
                if (text.length() > 16) { return false; }
            }
        }

        if (!number)
        {
            Show_Warning(L"当前输入的内容包含无效的 进制");
            return false;
        }
        
        Close_Warning();
        return true;
    }

    long long Endian::toNumeric(const std::string& v, winrt::hstring& mode)
    {
        long long numeric{ 0 };
        
        if (v == "")
        {
            return -2;
        }

        if (mode == hexTag)
        {
            numeric = stoll(v, nullptr, 16);
        }
        else if (mode == decTag)
        {
            numeric = stoll(v, nullptr, 10);
        }
        else
        {
            numeric = -1;
        }

        return numeric;
    }

    void Endian::BinarysTransform(const long long v, std::vector<winrt::hstring>& binaryviews)
    {
        auto binarytag = BinaryFilter();
        auto width = unbox_value<hstring>(ViewModel().CurrentDataWidths());
        winrt::hstring content;
        std::vector<winrt::hstring> rbinarys;

        binarytag.pop_back();
        for (auto bin = binarytag.begin(); bin != binarytag.end(); bin++)
        {
            if (width == width16Tag)
            {
                if (*bin == hexTag)
                {
                    content = winrt::to_hstring((boost::format("%x") % (unsigned short)v).str());
                }
                else if (*bin == decTag)
                {
                    content = winrt::to_hstring((boost::format("%u") % (unsigned short)v).str());
                }
                rbinarys.emplace_back(content);
            }
            else if (width == width32Tag)
            {
                if (*bin == hexTag)
                {
                    content = winrt::to_hstring((boost::format("%x") % (unsigned int)v).str());
                }
                else if (*bin == decTag)
                {
                    content = winrt::to_hstring((boost::format("%d") % (unsigned int)v).str());
                }
                rbinarys.emplace_back(content);
            }
            else if (width == width64Tag)
            {
                if (*bin == hexTag)
                {
                    content = winrt::to_hstring((boost::format("%lx") % (unsigned int)v).str());
                }
                else if (*bin == decTag)
                {
                    content = winrt::to_hstring((boost::format("%ld") % (unsigned int)v).str());
                }
                rbinarys.emplace_back(content);
            }
        }

        binaryviews = rbinarys;
    }

    void Endian::BitRowsTransform(const long long _row, const long long _reverse, std::string& row, std::string& reverse)
    {
        uint16_t row_idx = (uint16_t)(row.length() - 1);
        uint16_t rvs_idx = (uint16_t)(reverse.length() - 1);

        for (uint16_t i = 0; i < 64; i++)
        {
            uint16_t _rb = (_row >> i) & 1U;
            uint16_t _ib = (_reverse >> i) & 1U;

            if (row[row_idx] == ' ')
            {
                row_idx--;
            }
            if (reverse[rvs_idx] == ' ')
            {
                rvs_idx--;
            }

            if (_rb == 0)
            {
                row.replace(row_idx, 1, "0");
            }
            else if (_rb == 1)
            {
                row.replace(row_idx, 1, "1");
            }

            if (_ib == 0)
            {
                reverse.replace(rvs_idx, 1, "0");
            }
            else if (_ib == 1)
            {
                reverse.replace(rvs_idx, 1, "1");
            }
            row_idx--;
            rvs_idx--;
        }
    }

    void Endian::EndianTransform(winrt::hstring& str, winrt::hstring& revstr, std::vector<long long>& number, std::vector<long long>& rnumber)
    {
        auto bin = BinaryFilter().back();
        std::vector<string> textList;
        boost::split(textList, winrt::to_string(str), boost::is_any_of(" "), boost::token_compress_on);

        for (const auto& text : textList)
        {
            long long rc;
            rc = toNumeric(text, bin);
            if (rc == -2)
            {
                continue;
            }
            if (rc == -1)
            {
                Show_Warning(L"超出范围");
                return;
            }

            number.emplace_back(rc);
        }

        winrt::hstring numstr;
        auto width = unbox_value<hstring>(ViewModel().CurrentDataWidths());

        for (auto num = number.cbegin(); num != number.cend(); num++)
        {
            if (width == width16Tag)
            {
                auto revb = AtoB16((uint16_t)*num);
                if (bin == hexTag)
                {
                    numstr = winrt::to_hstring((boost::format("%04x") % (unsigned short)revb).str());
                }
                else if (bin == decTag)
                {
                    numstr = winrt::to_hstring((boost::format("%u") % (unsigned short)revb).str());
                }
                rnumber.emplace_back((long long)revb);
            }
            else if (width == width32Tag)
            {
                auto revb = AtoB32((uint32_t)*num);
                if (bin == hexTag)
                {
                    numstr = winrt::to_hstring((boost::format("%08x") % (unsigned int)revb).str());
                }
                else if (bin == decTag)
                {
                    numstr = winrt::to_hstring((boost::format("%d") % (unsigned int)revb).str());
                }
                rnumber.emplace_back((long long)revb);
            }
            else if (width == width64Tag)
            {
                auto revb = AtoB64(*num);
                if (bin == hexTag)
                {
                    numstr = winrt::to_hstring((boost::format("%016lx") % revb).str());
                }
                else if (bin == decTag)
                {
                    numstr = winrt::to_hstring((boost::format("%ld") % revb).str());
                }
                rnumber.emplace_back((long long)revb);
            }
            else
            {
                return ;
            }

            if (num == number.begin())
            {
                revstr = numstr;
            }
            else
            {
                revstr = revstr + L" " + numstr;
            }
        }
    }

    void Endian::EndianConvert(void)
    {
        std::vector<long long> _numberA;
        std::vector<long long> _numberB;
        std::vector<winrt::hstring> binaryview;
        winrt::hstring reverseEndian;
        winrt::hstring rowEndian{ EndianText().Text() };
        std::string rowbits{ winrt::to_string(RowBits().Text()) };
        std::string revbits{ winrt::to_string(ReverseBits().Text()) };

        EndianTransform(rowEndian, reverseEndian, _numberA, _numberB);
        if (_numberA.size() == 0)
        {
            rowbits = winrt::to_string(rowbitsTag);
            revbits = winrt::to_string(reversebitsTag);
            binaryview.emplace_back(hexContTag);
            binaryview.emplace_back(decContTag);
        }
        else
        {
            BitRowsTransform(_numberA[0], _numberB[0], rowbits, revbits);
            BinarysTransform(_numberA[0], binaryview);
        }

        Binary16().Text(binaryview[0]);
        Binary10().Text(binaryview[1]);
        RowBits().Text(winrt::to_hstring(rowbits));
        ReverseBits().Text(winrt::to_hstring(revbits));
        EndianReverse().Text(reverseEndian);
    }
}
