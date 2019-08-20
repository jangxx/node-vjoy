#pragma once

#include <node_api.h>
#include "../include/stdafx.h"
#include "../include/public.h"
#include "../include/vjoyinterface.h"

napi_value wrap_vJoyEnabled(napi_env env, napi_callback_info args);

napi_value wrap_GetvJoyVersion(napi_env env, napi_callback_info args);

napi_value wrap_GetvJoyProductString(napi_env env, napi_callback_info args);

napi_value wrap_GetvJoyManufacturerString(napi_env env, napi_callback_info args);

napi_value wrap_GetvJoySerialNumberString(napi_env env, napi_callback_info args);

napi_value wrap_DriverMatch(napi_env env, napi_callback_info args);

napi_value wrap_GetvJoyMaxDevices(napi_env env, napi_callback_info args);

napi_value wrap_GetNumberExistingVJD(napi_env env, napi_callback_info args);