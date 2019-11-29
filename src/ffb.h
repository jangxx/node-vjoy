#pragma once

#include "napi.h"
#include "../include/stdafx.h"
#include "../include/public.h"
#include "../include/vjoyinterface.h"
#include <map>

// Napi::Boolean wrap_FfbStart(const Napi::CallbackInfo& info);

// void wrap_FfbStop(const Napi::CallbackInfo& info);

Napi::Value wrap_Ffb_h_Eff_Report(Napi::Env env, const FFB_DATA* packet);
Napi::Value wrap_Ffb_h_Eff_Ramp(Napi::Env env, const FFB_DATA* packet);
Napi::Value wrap_Ffb_h_EffOp(Napi::Env env, const FFB_DATA* packet);
Napi::Value wrap_Ffb_h_Eff_Period(Napi::Env env, const FFB_DATA* packet);
Napi::Value wrap_Ffb_h_Eff_Cond(Napi::Env env, const FFB_DATA* packet);
Napi::Value wrap_Ffb_h_Eff_Envlp(Napi::Env env, const FFB_DATA* packet);
Napi::Value wrap_Ffb_h_Eff_Constant(Napi::Env env, const FFB_DATA* packet);

void wrap_FfbRegisterGenCB(const Napi::CallbackInfo& info);

Napi::Boolean wrap_IsDeviceFfb(const Napi::CallbackInfo& info);

Napi::Object getDeviceFfbEffects(const Napi::CallbackInfo& info);