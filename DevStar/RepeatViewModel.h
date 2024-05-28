#pragma once

#include "RepeatViewModel.g.h"

namespace winrt::DevStar::implementation
{
    struct RepeatViewModel : RepeatViewModelT<RepeatViewModel>
    {
        RepeatViewModel();
    };
}

namespace winrt::DevStar::factory_implementation
{
    struct RepeatViewModel : RepeatViewModelT<RepeatViewModel, implementation::RepeatViewModel>
    {
    };
}
