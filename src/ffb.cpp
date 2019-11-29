#include "ffb.h"

Napi::ThreadSafeFunction ffbCB_function = nullptr;

const std::map<FFBPType, std::string> ffbpTypeStrings = {
	{ PT_EFFREP, "PT_EFFREP" },
	{ PT_ENVREP, "PT_ENVREP" },
	{ PT_CONDREP, "PT_CONDREP" },
	{ PT_PRIDREP, "PT_PRIDREP" },
	{ PT_CONSTREP, "PT_CONSTREP" },
	{ PT_RAMPREP, "PT_RAMPREP" },
	{ PT_CSTMREP, "PT_CSTMREP" },
	{ PT_SMPLREP, "PT_SMPLREP" },
	{ PT_EFOPREP, "PT_EFOPREP" },
	{ PT_BLKFRREP, "PT_BLKFRREP" },
	{ PT_CTRLREP, "PT_CTRLREP" },
	{ PT_GAINREP, "PT_GAINREP" },
	{ PT_SETCREP, "PT_SETCREP" },
	{ PT_NEWEFREP, "PT_NEWEFREP", },
	{ PT_BLKLDREP, "PT_BLKLDREP", },
	{ PT_POOLREP, "PT_POOLREP" }
};

const std::map<FFBOP, std::string> ffbOpStrings = {
	{ EFF_START, "EFF_START" },
	{ EFF_SOLO, "EFF_SOLO" },
	{ EFF_STOP, "EFF_STOP" }
};

const std::map<FFB_CTRL, std::string> ffbCtrlStrings = {
	{ CTRL_ENACT, "CTRL_ENACT" },
	{ CTRL_DISACT, "CTRL_DISACT" },
	{ CTRL_STOPALL, "CTRL_STOPALL" },
	{ CTRL_DEVRST, "CTRL_DEVRST" },
	{ CTRL_DEVPAUSE, "CTRL_DEVPAUSE" },
	{ CTRL_DEVCONT, "CTRL_DEVCONT" },
};

// Napi::Boolean wrap_FfbStart(const Napi::CallbackInfo& info) {
// 	Napi::Env env = info.Env();

// 	UINT rID = info[0].As<Napi::Number>().Uint32Value();

// 	bool success = FfbStart(rID);

// 	return Napi::Boolean::New(env, success);
// }

// void wrap_FfbStop(const Napi::CallbackInfo& info) {
// 	Napi::Env env = info.Env();

// 	UINT rID = info[0].As<Napi::Number>().Uint32Value();

// 	FfbStop(rID);
// }

Napi::Value wrap_Ffb_h_Eff_Report(Napi::Env env, const FFB_DATA* packet) {
	FFB_EFF_REPORT effect;
	DWORD result = Ffb_h_Eff_Report(packet, &effect);

	if (result != ERROR_SUCCESS) {
		return env.Null();
	}

	Napi::Object ret = Napi::Object::New(env);
	ret.Set("effectBlockIndex", Napi::Number::New(env, (double)effect.EffectBlockIndex));
	ret.Set("effectType", Napi::Number::New(env, (double)effect.EffectType));
	ret.Set("duration", Napi::Number::New(env, (double)effect.Duration));
	ret.Set("trigerRpt", Napi::Number::New(env, (double)effect.TrigerRpt));
	ret.Set("samplePrd", Napi::Number::New(env, (double)effect.SamplePrd));
	ret.Set("gain", Napi::Number::New(env, (double)effect.Gain));
	ret.Set("trigerBtn", Napi::Number::New(env, (double)effect.TrigerBtn));
	ret.Set("polar", Napi::Boolean::New(env, effect.Polar == TRUE));

	if (effect.Polar == TRUE) {
		ret.Set("direction",  Napi::Number::New(env, (double)effect.Direction));
	} else {
		ret.Set("dirX",  Napi::Number::New(env, (double)effect.DirX));
		ret.Set("dirY",  Napi::Number::New(env, (double)effect.DirY));
	}

	return ret;
}

Napi::Value wrap_Ffb_h_Eff_Ramp(Napi::Env env, const FFB_DATA* packet) {
	FFB_EFF_RAMP effect;
	DWORD result = Ffb_h_Eff_Ramp(packet, &effect);

	if (result != ERROR_SUCCESS) {
		return env.Null();
	}

	Napi::Object ret = Napi::Object::New(env);
	ret.Set("effectBlockIndex", Napi::Number::New(env, (double)effect.EffectBlockIndex));
	ret.Set("start", Napi::Number::New(env, effect.Start));
	ret.Set("end", Napi::Number::New(env, effect.End));

	return ret;
}

Napi::Value wrap_Ffb_h_EffOp(Napi::Env env, const FFB_DATA* packet) {
	FFB_EFF_OP effect;
	DWORD result = Ffb_h_EffOp(packet, &effect);

	if (result != ERROR_SUCCESS) {
		return env.Null();
	}

	Napi::Object ret = Napi::Object::New(env);
	ret.Set("effectBlockIndex", Napi::Number::New(env, (double)effect.EffectBlockIndex));
	ret.Set("effectOp", Napi::String::New(env, ffbOpStrings.at(effect.EffectOp)));
	ret.Set("loopCount", Napi::Number::New(env, effect.LoopCount));

	return ret;
}

Napi::Value wrap_Ffb_h_Eff_Period(Napi::Env env, const FFB_DATA* packet) {
	FFB_EFF_PERIOD effect;
	DWORD result = Ffb_h_Eff_Period(packet, &effect);

	if (result != ERROR_SUCCESS) {
		return env.Null();
	}

	Napi::Object ret = Napi::Object::New(env);
	ret.Set("effectBlockIndex", Napi::Number::New(env, (double)effect.EffectBlockIndex));
	ret.Set("magnitude", Napi::Number::New(env, effect.Magnitude));
	ret.Set("offset", Napi::Number::New(env, effect.Offset));
	ret.Set("phase", Napi::Number::New(env, effect.Phase));
	ret.Set("period", Napi::Number::New(env, effect.Period));

	return ret;
}

Napi::Value wrap_Ffb_h_Eff_Cond(Napi::Env env, const FFB_DATA* packet) {
	FFB_EFF_COND effect;
	DWORD result = Ffb_h_Eff_Cond(packet, &effect);

	if (result != ERROR_SUCCESS) {
		return env.Null();
	}

	Napi::Object ret = Napi::Object::New(env);
	ret.Set("effectBlockIndex", Napi::Number::New(env, (double)effect.EffectBlockIndex));
	ret.Set("isY", Napi::Boolean::New(env, effect.isY == TRUE));
	ret.Set("centerPointOffset", Napi::Number::New(env, effect.CenterPointOffset));
	ret.Set("posCoeff", Napi::Number::New(env, effect.PosCoeff));
	ret.Set("negCoeff", Napi::Number::New(env, effect.NegCoeff));
	ret.Set("posSatur", Napi::Number::New(env, effect.PosSatur));
	ret.Set("negSatur", Napi::Number::New(env, effect.NegSatur));
	ret.Set("deadBand", Napi::Number::New(env, effect.DeadBand));

	return ret;
}

Napi::Value wrap_Ffb_h_Eff_Envlp(Napi::Env env, const FFB_DATA* packet) {
	FFB_EFF_ENVLP effect;
	DWORD result = Ffb_h_Eff_Envlp(packet, &effect);

	if (result != ERROR_SUCCESS) {
		return env.Null();
	}

	Napi::Object ret = Napi::Object::New(env);
	ret.Set("effectBlockIndex", Napi::Number::New(env, (double)effect.EffectBlockIndex));
	ret.Set("attackLevel", Napi::Number::New(env, (double)effect.AttackLevel));
	ret.Set("fadeLevel", Napi::Number::New(env, (double)effect.FadeLevel));
	ret.Set("attackTime", Napi::Number::New(env, (double)effect.AttackTime));
	ret.Set("fadeTime", Napi::Number::New(env, (double)effect.FadeTime));

	return ret;
}

Napi::Value wrap_Ffb_h_Eff_Constant(Napi::Env env, const FFB_DATA* packet) {
	FFB_EFF_CONSTANT effect;
	DWORD result = Ffb_h_Eff_Constant(packet, &effect);

	if (result != ERROR_SUCCESS) {
		return env.Null();
	}

	Napi::Object ret = Napi::Object::New(env);
	ret.Set("effectBlockIndex", Napi::Number::New(env, (double)effect.EffectBlockIndex));
	ret.Set("magnitude", Napi::Number::New(env, effect.Magnitude));

	return ret;
}

void FFBcallback(PVOID FfbPacket, PVOID userdata) {
	ffbCB_function.NonBlockingCall(FfbPacket, [](Napi::Env env, Napi::Function fn, PVOID packet) {
		FFB_DATA* data = (FFB_DATA*)packet;

		Napi::Object evt = Napi::Object::New(env);

		int deviceID = -1;
		DWORD result = Ffb_h_DeviceID(data, &deviceID);

		FFBPType type;
		result = Ffb_h_Type(data, &type);

		if (result == ERROR_SUCCESS) {
			evt.Set("type", Napi::String::New(env, ffbpTypeStrings.at(type)));

			switch (type) {
				case PT_EFFREP:
					evt.Set("effect", wrap_Ffb_h_Eff_Report(env, data));
					break;
				case PT_RAMPREP:
					evt.Set("effect", wrap_Ffb_h_Eff_Ramp(env, data));
					break;
				case PT_EFOPREP:
					evt.Set("effect", wrap_Ffb_h_EffOp(env, data));
					break;
				case PT_PRIDREP:
					evt.Set("effect", wrap_Ffb_h_Eff_Period(env, data));
					break;
				case PT_CONDREP:
					evt.Set("effect", wrap_Ffb_h_Eff_Cond(env, data));
					break;
				case PT_ENVREP:
					evt.Set("effect", wrap_Ffb_h_Eff_Envlp(env, data));
					break;
				default:
					evt.Set("effect", env.Null());
					break;
			}
		} else {
			evt.Set("type", env.Null());
			evt.Set("effect", env.Null());
		}

		int effectBlockIndex = -1;
		result = Ffb_h_EBI(data, &effectBlockIndex);
		evt.Set("ebi", Napi::Number::New(env, (double)effectBlockIndex));

		BYTE gain = 0;
		result = Ffb_h_DevGain(data, &gain);
		evt.Set("gain", Napi::Number::New(env, (double)gain));

		FFB_CTRL control;
		result = Ffb_h_DevCtrl(data, &control);
		if (result == ERROR_SUCCESS) {
			evt.Set("control", Napi::String::New(env, ffbCtrlStrings.at(control)));
		} else {
			evt.Set("control", env.Null());
		}

		// pass data to JS callback
		fn.Call({ Napi::Number::New(env, (double)deviceID), evt });

		// lets hope we don't have to clean up the other data
	});
}

void wrap_FfbRegisterGenCB(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	if (!info[0].IsFunction()) {
		Napi::Error::New(env, "The first parameter needs to be a function").ThrowAsJavaScriptException();
		return;
	}

	Napi::Function callback = info[0].As<Napi::Function>();
	ffbCB_function = Napi::ThreadSafeFunction::New(env, callback, "forcefeedbackCB", 0, 1);

	FfbRegisterGenCB(&FFBcallback, nullptr);
}

Napi::Boolean wrap_IsDeviceFfb(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	UINT rID = info[0].As<Napi::Number>().Uint32Value();

	bool ffbSupported = IsDeviceFfb(rID);

	return Napi::Boolean::New(env, ffbSupported);
}

Napi::Object getDeviceFfbEffects(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();

	UINT rID = info[0].As<Napi::Number>().Uint32Value();

	Napi::Object ret = Napi::Object::New(env);

	ret.Set("constant", Napi::Boolean::New(env, IsDeviceFfbEffect(rID, HID_USAGE_CONST) == TRUE));
	ret.Set("ramp", Napi::Boolean::New(env, IsDeviceFfbEffect(rID, HID_USAGE_RAMP) == TRUE));
	ret.Set("square", Napi::Boolean::New(env, IsDeviceFfbEffect(rID, HID_USAGE_SQUR) == TRUE));
	ret.Set("sine", Napi::Boolean::New(env, IsDeviceFfbEffect(rID, HID_USAGE_SINE) == TRUE));
	ret.Set("triangle", Napi::Boolean::New(env, IsDeviceFfbEffect(rID, HID_USAGE_TRNG) == TRUE));
	ret.Set("sawtooth_up", Napi::Boolean::New(env, IsDeviceFfbEffect(rID, HID_USAGE_STUP) == TRUE));
	ret.Set("sawtooth_down", Napi::Boolean::New(env, IsDeviceFfbEffect(rID, HID_USAGE_STDN) == TRUE));
	ret.Set("spring", Napi::Boolean::New(env, IsDeviceFfbEffect(rID, HID_USAGE_SPRNG) == TRUE));
	ret.Set("damper", Napi::Boolean::New(env, IsDeviceFfbEffect(rID, HID_USAGE_DMPR) == TRUE));
	ret.Set("inertia", Napi::Boolean::New(env, IsDeviceFfbEffect(rID, HID_USAGE_INRT) == TRUE));
	ret.Set("friction", Napi::Boolean::New(env, IsDeviceFfbEffect(rID, HID_USAGE_FRIC) == TRUE));

	return ret;
}