#include "napi.h"
#include "../include/stdafx.h"
#include "../include/public.h"
#include "../include/vjoyinterface.h"

#include "general.h"
#include "device.h"
#include "feeding.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
	exports.Set("vJoyEnabled", Napi::Function::New(env, wrap_vJoyEnabled));
	exports.Set("GetvJoyVersion", Napi::Function::New(env, wrap_GetvJoyVersion));
	exports.Set("GetvJoyProductString", Napi::Function::New(env, wrap_GetvJoyProductString));
	exports.Set("GetvJoyManufacturerString", Napi::Function::New(env, wrap_GetvJoyManufacturerString));
	exports.Set("GetvJoySerialNumberString", Napi::Function::New(env, wrap_GetvJoySerialNumberString));
	exports.Set("DriverMatch", Napi::Function::New(env, wrap_DriverMatch));
	exports.Set("GetvJoyMaxDevices", Napi::Function::New(env, wrap_GetvJoyMaxDevices));
	exports.Set("GetNumberExistingVJD", Napi::Function::New(env, wrap_GetNumberExistingVJD));
	// exports.Set("RegisterRemovalCB", Napi::Function::New(env, wrap_RegisterRemovalCB));

	exports.Set("GetVJDButtonNumber", Napi::Function::New(env, wrap_GetVJDButtonNumber));
	exports.Set("GetVJDDiscPovNumber", Napi::Function::New(env, wrap_GetVJDDiscPovNumber));
	exports.Set("GetVJDContPovNumber", Napi::Function::New(env, wrap_GetVJDContPovNumber));
	exports.Set("GetVJDAxisExists", Napi::Function::New(env, wrap_GetVJDAxisExists));
	exports.Set("GetVJDStatus", Napi::Function::New(env, wrap_GetVJDStatus));
	exports.Set("isVJDExists", Napi::Function::New(env, wrap_isVJDExists));

	exports.Set("AcquireVJD", Napi::Function::New(env, wrap_AcquireVJD));
	exports.Set("RelinquishVJD", Napi::Function::New(env, wrap_RelinquishVJD));
	exports.Set("ResetVJD", Napi::Function::New(env, wrap_ResetVJD));
	exports.Set("ResetButtons", Napi::Function::New(env, wrap_ResetButtons));
	exports.Set("ResetPovs", Napi::Function::New(env, wrap_ResetPovs));
	exports.Set("SetAxis", Napi::Function::New(env, wrap_SetAxis));
	exports.Set("SetBtn", Napi::Function::New(env, wrap_SetBtn));
	exports.Set("SetDiscPov", Napi::Function::New(env, wrap_SetDiscPov));
	exports.Set("SetContPov", Napi::Function::New(env, wrap_SetContPov));

	return exports;
}

NODE_API_MODULE(vjoy, Init)