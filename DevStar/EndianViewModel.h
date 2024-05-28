#pragma once

#include "EndianViewModel.g.h"
#include "EndianView.g.h"
#include "Utils.h"
#include "ViewModelHelpers.h"

namespace winrt::DevStar::implementation
{
    struct EndianView : EndianViewT<EndianView>
    {
        EndianView();
        EndianView(const winrt::hstring& w);

        WINRT_PROPERTY(winrt::hstring, Binary,);
    };

    struct EndianViewModel : EndianViewModelT<EndianViewModel>, ViewModelHelper<EndianViewModel>
    {
        EndianViewModel();

        WINRT_PROPERTY(DevStar::EndianView, CurrentBinary, L"Binary_16");
        WINRT_PROPERTY(Windows::Foundation::Collections::IObservableVector<DevStar::EndianView>, BinaryList);
        GETSET_BINDABLE_ENUM_SETTING(DataWidths, Windows::Foundation::Collections::IObservableVector<winrt::hstring>, L"Width_32");
    };
}

namespace winrt::DevStar::factory_implementation
{
    struct EndianView : EndianViewT<EndianView, implementation::EndianView>
    {
    };

    struct EndianViewModel : EndianViewModelT<EndianViewModel, implementation::EndianViewModel>
    {
    };
}

