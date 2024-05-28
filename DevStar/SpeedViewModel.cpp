#include "pch.h"

#include "SpeedViewModel.h"
#if __has_include("SpeedViewModel.g.cpp")
#include "SpeedViewModel.g.cpp"
#endif

#include "FallSerializationHelpers.h"
#include "LibraryResources.h"

namespace winrt::DevStar::implementation
{
	SpeedViewModel::SpeedViewModel()
	{
		INITIALIZE_BINDABLE_ENUM_SETTING(Protocol, Protocols, L"Content");
		INITIALIZE_BINDABLE_ENUM_SETTING(SerialSpeed, Serials, L"Content");
		INITIALIZE_BINDABLE_ENUM_SETTING(USBSpeed, USBs, L"Content");
		INITIALIZE_BINDABLE_ENUM_SETTING(EthernetSpeed, Ethernets, L"Content");
		INITIALIZE_BINDABLE_ENUM_SETTING(WIFISpeed, WIFIs, L"Content");
		INITIALIZE_BINDABLE_ENUM_SETTING(RS232Speed, RS232s, L"Content");
		INITIALIZE_BINDABLE_ENUM_SETTING(RS485Speed, RS485s, L"Content");
		INITIALIZE_BINDABLE_ENUM_SETTING(SPISpeed, SPIs, L"Content");
		INITIALIZE_BINDABLE_ENUM_SETTING(I2CSpeed, I2Cs, L"Content");
		INITIALIZE_BINDABLE_ENUM_SETTING(CANSpeed, CANs, L"Content");
		INITIALIZE_BINDABLE_ENUM_SETTING(BluetoothSpeed, Bluetooths, L"Content");
		INITIALIZE_BINDABLE_ENUM_SETTING(PCIESpeed, PCIEs, L"Content");
	}
}
