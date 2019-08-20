#include <node_api.h>
#include "../include/stdafx.h"
#include "../include/public.h"
#include "../include/vjoyinterface.h"

#include "general.h"

// macro to create a JS function object and attach it to the exports object. Only works in the init function.
#define NAPI_FUNC(fn_name, exported_name) napi_value fn_##fn_name; \
                           status = napi_create_function(env, nullptr, 0, fn_name, nullptr, &fn_##fn_name); if (status != napi_ok) return nullptr; \
                           status = napi_set_named_property(env, exports, exported_name, fn_##fn_name); if (status != napi_ok) return nullptr;

napi_value init(napi_env env, napi_value exports) {
	napi_status status;

	NAPI_FUNC(wrap_vJoyEnabled, "vJoyEnabled")
	NAPI_FUNC(wrap_GetvJoyVersion, "GetvJoyVersion")
	NAPI_FUNC(wrap_GetvJoyProductString, "GetvJoyProductString")
	NAPI_FUNC(wrap_GetvJoyManufacturerString, "GetvJoyManufacturerString")
	NAPI_FUNC(wrap_GetvJoySerialNumberString, "GetvJoySerialNumberString")
	NAPI_FUNC(wrap_DriverMatch, "DriverMatch")
	NAPI_FUNC(wrap_GetvJoyMaxDevices, "GetvJoyMaxDevices")
	NAPI_FUNC(wrap_GetNumberExistingVJD, "GetNumberExistingVJD")

	return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)