#pragma once

#include "MemorySpaceViewModel.g.h"

namespace winrt::DevStar::implementation
{
    struct MemorySpaceViewModel : MemorySpaceViewModelT<MemorySpaceViewModel>
    {
        MemorySpaceViewModel();
    };
}

namespace winrt::DevStar::factory_implementation
{
    struct MemorySpaceViewModel : MemorySpaceViewModelT<MemorySpaceViewModel, implementation::MemorySpaceViewModel>
    {
    };
}
