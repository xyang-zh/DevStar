#pragma once

#include "CRCViewModel.g.h"
#include "Utils.h"
#include "ViewModelHelpers.h"

namespace winrt::DevStar::implementation
{
    struct CRCViewModel : CRCViewModelT<CRCViewModel>, ViewModelHelper<CRCViewModel>
    {
        CRCViewModel();

        GETSET_BINDABLE_ENUM_SETTING(CRC, Windows::Foundation::Collections::IObservableVector<winrt::hstring>, L"CRC_32");
    };
}

namespace winrt::DevStar::factory_implementation
{
    struct CRCViewModel : CRCViewModelT<CRCViewModel, implementation::CRCViewModel>
    {
    };
}
