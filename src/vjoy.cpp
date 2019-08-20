#include "napi.h"
#include "../include/stdafx.h"
#include "../include/public.h"
#include "../include/vjoyinterface.h"

#include "general.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
	exports.Set("vJoyEnabled", Napi::Function::New(env, wrap_vJoyEnabled));
	exports.Set("GetvJoyVersion", Napi::Function::New(env, wrap_GetvJoyVersion));
	exports.Set("GetvJoyProductString", Napi::Function::New(env, wrap_GetvJoyProductString));
	exports.Set("GetvJoyManufacturerString", Napi::Function::New(env, wrap_GetvJoyManufacturerString));
	exports.Set("GetvJoySerialNumberString", Napi::Function::New(env, wrap_GetvJoySerialNumberString));
	exports.Set("DriverMatch", Napi::Function::New(env, wrap_DriverMatch));
	exports.Set("GetvJoyMaxDevices", Napi::Function::New(env, wrap_GetvJoyMaxDevices));
	exports.Set("GetNumberExistingVJD", Napi::Function::New(env, wrap_GetNumberExistingVJD));

	return exports;
}

NODE_API_MODULE(vjoy, Init)