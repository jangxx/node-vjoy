#pragma once

#include "napi.h"
#include "../include/stdafx.h"
#include "../include/public.h"
#include "../include/vjoyinterface.h"

// napi_value wrap_vJoyEnabled(napi_env env, napi_callback_info args);

Napi::Boolean wrap_vJoyEnabled(const Napi::CallbackInfo& info);

Napi::Number wrap_GetvJoyVersion(const Napi::CallbackInfo& info);

Napi::String wrap_GetvJoyProductString(const Napi::CallbackInfo& info);

Napi::String wrap_GetvJoyManufacturerString(const Napi::CallbackInfo& info);

Napi::String wrap_GetvJoySerialNumberString(const Napi::CallbackInfo& info);

Napi::Object wrap_DriverMatch(const Napi::CallbackInfo& info);

Napi::Number wrap_GetvJoyMaxDevices(const Napi::CallbackInfo& info);

Napi::Number wrap_GetNumberExistingVJD(const Napi::CallbackInfo& info);