#pragma once

#include "Path.g.h"
#include "PathViewModel.h"
#include "Utils.h"
#include "ViewModelHelpers.h"

namespace winrt::DevStar::implementation
{
    struct Path : PathT<Path>
    {
        Path();

        WINRT_PROPERTY(DevStar::PathViewModel, ViewModel);

    public:
        void PathPanel_Loaded(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::RoutedEventArgs const& e);
        void SystemChanged(Windows::Foundation::IInspectable const& sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void PathTextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::Controls::TextChangedEventArgs const& e);
        void ClearButtonClicked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

        void UpdatePath(winrt::hstring& p);
    };
}

namespace winrt::DevStar::factory_implementation
{
    struct Path : PathT<Path, implementation::Path>
    {
    };
}
