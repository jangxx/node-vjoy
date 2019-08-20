#include "general.h"
#include "utils.h"

napi_value wrap_vJoyEnabled(napi_env env, napi_callback_info args) {
	napi_status status;
	napi_value res;

	bool enabled = vJoyEnabled();

	status = napi_get_boolean(env, enabled, &res);
	if (status != napi_ok) return nullptr;

	return res;
}

napi_value wrap_GetvJoyVersion(napi_env env, napi_callback_info args) {
	napi_status status;
	napi_value res;

	short version = GetvJoyVersion();

	status = napi_create_uint32(env, version, &res);
	if (status != napi_ok) return nullptr;

	return res;
}

napi_value wrap_GetvJoyProductString(napi_env env, napi_callback_info args) {
	napi_status status;
	napi_value res;

	PVOID p_prodString = GetvJoyProductString();

	std::string prodString = utf8_encode((PWSTR)p_prodString);

	CoTaskMemFree(p_prodString);

	status = napi_create_string_utf8(env, prodString.c_str(), NAPI_AUTO_LENGTH, &res);
	if (status != napi_ok) return nullptr;

	return res;
}

napi_value wrap_GetvJoyManufacturerString(napi_env env, napi_callback_info args) {
	napi_status status;
	napi_value res;

	PVOID p_manuString = GetvJoyManufacturerString();

	std::string manuString = utf8_encode((PWSTR)p_manuString);

	CoTaskMemFree(p_manuString);

	status = napi_create_string_utf8(env, manuString.c_str(), NAPI_AUTO_LENGTH, &res);
	if (status != napi_ok) return nullptr;

	return res;
}

napi_value wrap_GetvJoySerialNumberString(napi_env env, napi_callback_info args) {
	napi_status status;
	napi_value res;

	PVOID p_serialString = GetvJoySerialNumberString();

	std::string serialString = utf8_encode((PWSTR)p_serialString);

	CoTaskMemFree(p_serialString);

	status = napi_create_string_utf8(env, serialString.c_str(), NAPI_AUTO_LENGTH, &res);
	if (status != napi_ok) return nullptr;

	return res;
}

napi_value wrap_DriverMatch(napi_env env, napi_callback_info args) {
	napi_status status;
	napi_value var_matches, var_dllversion, var_drvversion, res;

	WORD DllVersion;
	WORD DrvVersion;

	bool matches = DriverMatch(&DllVersion, &DrvVersion);

	status = napi_get_boolean(env, matches, &var_matches);
	if (status != napi_ok) return nullptr;

	status = napi_create_uint32(env, DllVersion, &var_dllversion);
	if (status != napi_ok) return nullptr;

	status = napi_create_uint32(env, DrvVersion, &var_drvversion);
	if (status != napi_ok) return nullptr;

	// Create return object
	status = napi_create_object(env, &res);
	if (status != napi_ok) return nullptr;

	// Add return object properties
	status = napi_set_named_property(env, res, "matches", var_matches);
	if (status != napi_ok) return nullptr;
	status = napi_set_named_property(env, res, "dll_version", var_dllversion);
	if (status != napi_ok) return nullptr;
	status = napi_set_named_property(env, res, "drv_version", var_drvversion);
	if (status != napi_ok) return nullptr;

	return res;
}

napi_value wrap_GetvJoyMaxDevices(napi_env env, napi_callback_info args) {
	napi_status status;
	napi_value res;

	int maxDevices;

	GetvJoyMaxDevices(&maxDevices);

	status = napi_create_uint32(env, maxDevices, &res);
	if (status != napi_ok) return nullptr;

	return res;
}

napi_value wrap_GetNumberExistingVJD(napi_env env, napi_callback_info args) {
	napi_status status;
	napi_value res;

	int existingVJD;

	GetNumberExistingVJD(&existingVJD);

	status = napi_create_uint32(env, existingVJD, &res);
	if (status != napi_ok) return nullptr;

	return res;
}