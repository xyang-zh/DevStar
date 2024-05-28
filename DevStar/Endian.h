#pragma once

#include <cstdlib>
#include "Endian.g.h"
#include "EndianViewModel.h"
#include "Utils.h"

namespace winrt::DevStar::implementation
{
    struct Endian : EndianT<Endian>
    {
        Endian();

        WINRT_PROPERTY(bool, TransModel, true);
        WINRT_PROPERTY(bool, EndianModel, true);
        WINRT_PROPERTY(DevStar::EndianViewModel, ViewModel);

    public:
        void EndiansPanel_Loaded(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);
        void BinarysList_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void DataWidth_Changed(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void EndianContents_Changed(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::TextChangedEventArgs const& e);
        void ClearButtonClicked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void Close_Warning(void);
        void Show_Warning(const winrt::hstring& w);
        void EndianConvert(void);

        bool IsContentValid(void);
        uint64_t AtoB64(uint64_t a);
        uint32_t AtoB32(uint32_t a);
        uint16_t AtoB16(uint16_t a);
        std::vector<winrt::hstring> BinaryFilter(void);
        long long toNumeric(const std::string& v, winrt::hstring& mode);
        void BitRowsTransform(const long long _row, const long long _reverse, std::string& row, std::string& reverse);
        void BinarysTransform(const long long v, std::vector<winrt::hstring>& binaryviews);
        void EndianTransform(winrt::hstring& str, winrt::hstring& revstr, std::vector<long long>& number, std::vector<long long>& rnumber);
    };
}

namespace winrt::DevStar::factory_implementation
{
    struct Endian : EndianT<Endian, implementation::Endian>
    {
    };
}
