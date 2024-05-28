#include "pch.h"

#include "EndianViewModel.h"
#if __has_include("EndianViewModel.g.cpp")
#include "EndianViewModel.g.cpp"
#endif

#if __has_include("EndianView.g.cpp")
#include "EndianView.g.cpp"
#endif

#include "LibraryResources.h"
#include "FallSerializationHelpers.h"

using namespace winrt;
using namespace Windows::UI::Xaml::Data;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;

namespace winrt::DevStar::implementation
{
	EndianView::EndianView()
	{
	}

	EndianView::EndianView(const winrt::hstring& w) : _Binary{ w }
	{
	}

	EndianViewModel::EndianViewModel()
	{
		PropertyChanged([this](auto&&, const PropertyChangedEventArgs& args) {
			const auto viewModelProperty{ args.PropertyName() };
			// if (viewModelProperty == L"StartingDirectory")
			//{
			//    // notify listener that all starting directory related values might have changed
			//    // NOTE: this is similar to what is done with BackgroundImagePath above
			//    _NotifyChanges(L"UseParentProcessDirectory", L"UseCustomStartingDirectory");
			//}           
			});


		INITIALIZE_BINDABLE_CONTA_SETTING(DevStar, EndianView, Binary, Binary, L"Content");
		INITIALIZE_BINDABLE_ENUM_SETTING(DataWidths, DataWidths, L"Content");
	}
}

UTILS_DEFINE_LIBRARY_RESOURCE_SCOPE(L"Resources");