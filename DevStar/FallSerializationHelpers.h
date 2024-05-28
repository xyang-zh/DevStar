#pragma once

#include "pch.h"

//all the tools
static std::array <winrt::hstring, 21> CRCAlgo = { 
	L"CRC_4_ITU",
	L"CRC_5_EPC",
	L"CRC_5_ITU",
	L"CRC_5_USB",
	L"CRC_6_ITU",
	L"CRC_7_MMC",
	L"CRC_8",
	L"CRC_8_ITU",
	L"CRC_8_ROHC",
	L"CRC_8_MAXIM",
	L"CRC_16_IBM",
	L"CRC_16_MAXIM",
	L"CRC_16_USB",
	L"CRC_16_MODBUS",
	L"CRC_16_CCITT",
	L"CRC_16_CCITT_FALSE",
	L"CRC_16_X25",
	L"CRC_16_XMODEM",
	L"CRC_16_DNP",
	L"CRC_32",
	L"CRC_32_MPEG_2"
};

static std::array <winrt::hstring, 2> Binary = {
	L"Binary_16",
	L"Binary_10"
};

static std::array <winrt::hstring, 3> DataWidths = {
	L"Width_16",
	L"Width_32",
	L"Width_64"
};

static std::array <winrt::hstring, 11> Protocols = {
	L"Serial",
	L"USB",
	L"Ethernet",
	L"WIFI",
	L"RS232",
	L"RS485",
	L"SPI",
	L"I2C",
	L"CAN",
	L"Bluetooth",
	L"PCIE"
};

// bps
static std::array <winrt::hstring, 16> Serials = {
	L"Serial_300",
	L"Serial_600",
	L"Serial_1200",
	L"Serial_2400",
	L"Serial_4800",
	L"Serial_9600",
	L"Serial_14400",
	L"Serial_19200",
	L"Serial_28800",
	L"Serial_38400",
	L"Serial_57600",
	L"Serial_115200",
	L"Serial_230400",
	L"Serial_380400",
	L"Serial_460800",
	L"Serial_921600"
};

// bps
static std::array <winrt::hstring, 5> USBs = {
	L"USB_1p5M",
	L"USB_12M",
	L"USB_480M",
	L"USB_5G",
	L"USB_10G"
};

// bps
static std::array <winrt::hstring, 5> Ethernets = {
	L"ETH_3M",
	L"ETH_10M",
	L"ETH_100M",
	L"ETH_1000M",
	L"ETH_10000M"
};

// bps
static std::array <winrt::hstring, 6> WIFIs = {
	L"WIFI_11M",
	L"WIFI_54M",
	L"WIFI_150M",
	L"WIFI_633M",
	L"WIFI_6p9G",
	L"WIFI_9p6G"
};

// bps
static std::array <winrt::hstring, 11> RS232s = {
	L"RS232_50",
	L"RS232_75",
	L"RS232_110",
	L"RS232_150",
	L"RS232_300",
	L"RS232_600",
	L"RS232_1200",
	L"RS232_2400",
	L"RS232_4800",
	L"RS232_9600",
	L"RS232_19200"
};

// bps
static std::array <winrt::hstring, 6> RS485s = {
	L"RS485_9600",
	L"RS485_14400",
	L"RS485_19200",
	L"RS485_38400",
	L"RS485_56000",
	L"RS485_115200"
};

// bps 
static std::array <winrt::hstring, 3> SPIs = {
	L"SPI_100K",
	L"SPI_2M",
	L"SPI_10M"
};

// bps
static std::array <winrt::hstring, 3> I2Cs = {
	L"I2C_100K",
	L"I2C_400K",
	L"I2C_3p4M"
};

// bps
static std::array <winrt::hstring, 9> CANs = {
	L"CAN_5K",
	L"CAN_10K",
	L"CAN_20K",
	L"CAN_40K",
	L"CAN_80K",
	L"CAN_160K",
	L"CAN_320K",
	L"CAN_800K",
	L"CAN_1M"
};

// bps
static std::array <winrt::hstring, 20> PCIEs = {
	L"PCIE1_x1_250M",
	L"PCIE1_x4_1G",
	L"PCIE1_x8_2G",
	L"PCIE1_x16_4G",
	L"PCIE2_x1_500M",
	L"PCIE2_x4_2G",
	L"PCIE2_x8_4G",
	L"PCIE2_x16_8G",
	L"PCIE3_x1_984p6M",
	L"PCIE3_x4_3p938G",
	L"PCIE3_x8_7p877G",
	L"PCIE3_x16_15p754G",
	L"PCIE4_x1_1p969G",
	L"PCIE4_x4_7p877G",
	L"PCIE4_x8_15p754G",
	L"PCIE4_x16_31p508G",
	L"PCIE5_x1_3p08G",
	L"PCIE5_x4_12p3G",
	L"PCIE5_x8_24p6G",
	L"PCIE5_x16_49p2G"
};

static std::array <winrt::hstring, 6> Bluetooths = {
	L"Blueth_125K",
	L"Blueth_1M",
	L"Blueth_2M",
	L"Blueth_3M",
	L"Blueth_24M",
	L"Blueth_48M"
};

static std::array <winrt::hstring, 2> Systems = {
	L"Windows",
	L"Linux"
};

static std::array <winrt::hstring, 4> Methods = {
	L"Default",
	L"Odd",
	L"Even",
	L"Custom"
};

static std::array <winrt::hstring, 2> ImplMethods = {
	L"Nearest",
	L"Align"
};

static std::array <winrt::hstring, 2> ImplModes = {
	L"Auto",
	L"ForceImplementation"
};
