#include "pch.h"

#include "CRCViewModel.h"
#if __has_include("CRCViewModel.g.cpp")
#include "CRCViewModel.g.cpp"
#endif

#include "LibraryResources.h"
#include "FallSerializationHelpers.h"

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;

namespace winrt::DevStar::implementation
{
	CRCViewModel::CRCViewModel()
	{
		INITIALIZE_BINDABLE_ENUM_SETTING(CRC, CRCAlgo, L"Content");
	}
}

UTILS_DEFINE_LIBRARY_RESOURCE_SCOPE(L"Resources");