#pragma once

#include "PathViewModel.g.h"
#include "Utils.h"
#include "ViewModelHelpers.h"

namespace winrt::DevStar::implementation
{
    struct PathViewModel : PathViewModelT<PathViewModel>, ViewModelHelper<PathViewModel>
    {
        PathViewModel();

        GETSET_BINDABLE_ENUM_SETTING(System, Windows::Foundation::Collections::IObservableVector<winrt::hstring>, L"Windows");
    };
}

namespace winrt::DevStar::factory_implementation
{
    struct PathViewModel : PathViewModelT<PathViewModel, implementation::PathViewModel>
    {
    };
}
