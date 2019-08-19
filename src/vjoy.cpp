#include <node_api.h>
#include "../include/stdafx.h"
#include "../include/public.h"
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "../include/vjoyinterface.h"

napi_value vjoy_enabled(napi_env env, napi_callback_info args) {
	napi_status status;
	napi_value res;

	bool enabled = vJoyEnabled();

	status = napi_get_boolean(env, true, &res);
	if (status != napi_ok) return nullptr;

	return res;
}

napi_value init(napi_env env, napi_value exports) {
	napi_status status;
	napi_value fn_vjoy_enabled;

	status = napi_create_function(env, nullptr, 0, vjoy_enabled, nullptr, &fn_vjoy_enabled);
	if (status != napi_ok) return nullptr;

	status = napi_set_named_property(env, exports, "vjoy_enabled", fn_vjoy_enabled);
	if (status != napi_ok) return nullptr;

	return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)