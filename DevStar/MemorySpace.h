#pragma once

#include "MemorySpace.g.h"

namespace winrt::DevStar::implementation
{
    struct MemorySpace : MemorySpaceT<MemorySpace>
    {
        MemorySpace();

        void MemorySpaceTextChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::TextChangedEventArgs const& e);
        void ClearButtonClicked(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);

        bool SizeValid(winrt::hstring& p);
        double UnitSize(std::string p);
        void UpdateSize(winrt::hstring & p);
    };
}

namespace winrt::DevStar::factory_implementation
{
    struct MemorySpace : MemorySpaceT<MemorySpace, implementation::MemorySpace>
    {
    };
}
