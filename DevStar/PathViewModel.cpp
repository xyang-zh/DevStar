#include "pch.h"

#include "PathViewModel.h"
#if __has_include("PathViewModel.g.cpp")
#include "PathViewModel.g.cpp"
#endif

#include "LibraryResources.h"
#include "FallSerializationHelpers.h"

namespace winrt::DevStar::implementation
{
	PathViewModel::PathViewModel()
	{
		INITIALIZE_BINDABLE_ENUM_SETTING(System, Systems, L"Content");
	}

}
