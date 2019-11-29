#pragma once

#include "napi.h"
#include "../include/stdafx.h"
#include "../include/public.h"
#include "../include/vjoyinterface.h"

typedef struct {
	bool removed;
	bool first;
} RemovalCBData;

Napi::Boolean wrap_vJoyEnabled(const Napi::CallbackInfo& info);

Napi::Number wrap_GetvJoyVersion(const Napi::CallbackInfo& info);

Napi::String wrap_GetvJoyProductString(const Napi::CallbackInfo& info);

Napi::String wrap_GetvJoyManufacturerString(const Napi::CallbackInfo& info);

Napi::String wrap_GetvJoySerialNumberString(const Napi::CallbackInfo& info);

Napi::Object wrap_DriverMatch(const Napi::CallbackInfo& info);

Napi::Number wrap_GetvJoyMaxDevices(const Napi::CallbackInfo& info);

Napi::Number wrap_GetNumberExistingVJD(const Napi::CallbackInfo& info);

void wrap_RegisterRemovalCB(const Napi::CallbackInfo& info);