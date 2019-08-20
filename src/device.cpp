#include "device.h"
#include "utils.h"

Napi::Number wrap_GetVJDButtonNumber(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	UINT rID = info[0].As<Napi::Number>().Uint32Value();
	
	int buttonNumber = GetVJDButtonNumber(rID);

	return Napi::Number::New(env, (double)buttonNumber);
}

Napi::Number wrap_GetVJDDiscPovNumber(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	UINT rID = info[0].As<Napi::Number>().Uint32Value();
	
	int discPovNumber = GetVJDDiscPovNumber(rID);

	return Napi::Number::New(env, (double)discPovNumber);
}

Napi::Number wrap_GetVJDContPovNumber(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	UINT rID = info[0].As<Napi::Number>().Uint32Value();
	
	int contPovNumber = GetVJDDiscPovNumber(rID);

	return Napi::Number::New(env, (double)contPovNumber);
}

Napi::Boolean wrap_GetVJDAxisExists(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	UINT rID = info[0].As<Napi::Number>().Uint32Value();
	std::string axis = info[1].As<Napi::String>().ToString();

	if (AxisMap.count(axis) == 0) {
		Napi::Error::New(env, "Invalid axis").ThrowAsJavaScriptException();
 		return Napi::Boolean::Boolean();
	}

	UINT axisID = AxisMap.at(axis);

	bool exists = GetVJDAxisExist(rID, axisID);

	return Napi::Boolean::New(env, exists);
}

Napi::String wrap_GetVJDStatus(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	UINT rID = info[0].As<Napi::Number>().Uint32Value();
	
	VjdStat status = GetVJDStatus(rID);

	switch (status) {
		case VJD_STAT_OWN:
			return Napi::String::New(env, "VJD_STAT_OWN");
		case VJD_STAT_FREE:
			return Napi::String::New(env, "VJD_STAT_FREE");
		case VJD_STAT_BUSY:
			return Napi::String::New(env, "VJD_STAT_BUSY");
		case VJD_STAT_MISS:
			return Napi::String::New(env, "VJD_STAT_MISS");
		case VJD_STAT_UNKN:
		default:
			return Napi::String::New(env, "VJD_STAT_UNKN");
	}
}

Napi::Boolean wrap_isVJDExists(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	UINT rID = info[0].As<Napi::Number>().Uint32Value();
	
	bool exists = isVJDExists(rID);

	return Napi::Boolean::New(env, exists);
}