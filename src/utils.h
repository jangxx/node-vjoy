#pragma once

#include "../include/stdafx.h"
#include "../include/public.h"
#include "../include/vjoyinterface.h"

std::string utf8_encode(const std::wstring &wstr);

const static std::unordered_map<std::string, uint8_t> AxisMap{
	{ "X", HID_USAGE_X },
	{ "Y", HID_USAGE_Y },
	{ "Z", HID_USAGE_Z },
	{ "Rx", HID_USAGE_RX },
	{ "Ry", HID_USAGE_RY },
	{ "Rz", HID_USAGE_RZ },
	{ "Slider0", HID_USAGE_SL0 },
	{ "Slider1", HID_USAGE_SL1 },
	{ "Wheel", HID_USAGE_WHL },
	{ "POV", HID_USAGE_POV },
};