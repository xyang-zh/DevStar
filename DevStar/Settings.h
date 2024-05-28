#pragma once

#include "Settings.g.h"

#include "Utils.h"
#include "ViewModelHelpers.h"

namespace winrt::DevStar::implementation
{
    struct Settings : SettingsT<Settings>
    {
        Settings();
    };
}

namespace winrt::DevStar::factory_implementation
{
    struct Settings : SettingsT<Settings, implementation::Settings>
    {
    };
}
