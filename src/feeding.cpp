#include "feeding.h"
#include "utils.h"

Napi::Boolean wrap_AcquireVJD(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	UINT rID = info[0].As<Napi::Number>().Uint32Value();

	bool result = AcquireVJD(rID);

	return Napi::Boolean::New(env, result);
}

void wrap_RelinquishVJD(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	UINT rID = info[0].As<Napi::Number>().Uint32Value();

	RelinquishVJD(rID);
}

Napi::Boolean wrap_ResetVJD(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	UINT rID = info[0].As<Napi::Number>().Uint32Value();

	bool result = ResetVJD(rID);

	return Napi::Boolean::New(env, result);
}

Napi::Boolean wrap_ResetButtons(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	UINT rID = info[0].As<Napi::Number>().Uint32Value();

	bool result = ResetButtons(rID);

	return Napi::Boolean::New(env, result);
}

Napi::Boolean wrap_ResetPovs(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	UINT rID = info[0].As<Napi::Number>().Uint32Value();

	bool result = ResetPovs(rID);

	return Napi::Boolean::New(env, result);
}

Napi::Boolean wrap_SetAxis(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	UINT rID = info[0].As<Napi::Number>().Uint32Value();
	std::string axis = info[1].As<Napi::String>().ToString();

	long value = info[2].As<Napi::Number>().Uint32Value();

	if (AxisMap.count(axis) == 0) {
		Napi::Error::New(env, "Invalid axis").ThrowAsJavaScriptException();
 		return Napi::Boolean::Boolean();
	}

	if (value < 1 || value > 0x8000) {
		Napi::Error::New(env, "Axis value out of range").ThrowAsJavaScriptException();
 		return Napi::Boolean::Boolean();
	}

	UINT axisID = AxisMap.at(axis);

	bool result = SetAxis(value, rID, axisID);

	return Napi::Boolean::New(env, result);
}

Napi::Boolean wrap_SetBtn(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	UINT rID = info[0].As<Napi::Number>().Uint32Value();
	uint8_t button = info[1].As<Napi::Number>().Uint32Value();

	bool value = info[2].As<Napi::Boolean>().ToBoolean();
	
	if (button < 1 || button > 128) {
		Napi::Error::New(env, "Button number out of range").ThrowAsJavaScriptException();
 		return Napi::Boolean::Boolean();
	}

	bool result = SetBtn(value, rID, button);

	return Napi::Boolean::New(env, result);
}

Napi::Boolean wrap_SetDiscPov(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	UINT rID = info[0].As<Napi::Number>().Uint32Value();
	uint8_t pov = info[1].As<Napi::Number>().Uint32Value();

	int value = info[2].As<Napi::Number>().Int32Value();

	if (pov < 1 || pov > 4) {
		Napi::Error::New(env, "POV number out of range").ThrowAsJavaScriptException();
 		return Napi::Boolean::Boolean();
	}

	bool result = SetDiscPov(value, rID, pov);

	return Napi::Boolean::New(env, result);
}

Napi::Boolean wrap_SetContPov(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	UINT rID = info[0].As<Napi::Number>().Uint32Value();
	uint8_t pov = info[1].As<Napi::Number>().Uint32Value();

	int value = info[2].As<Napi::Number>().Int32Value();

	if (pov < 1 || pov > 4) {
		Napi::Error::New(env, "POV number out of range").ThrowAsJavaScriptException();
 		return Napi::Boolean::Boolean();
	}

	bool result = SetContPov(value, rID, pov);

	return Napi::Boolean::New(env, result);
}