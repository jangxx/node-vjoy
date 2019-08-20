#pragma once

#include "napi.h"
#include "../include/stdafx.h"
#include "../include/public.h"
#include "../include/vjoyinterface.h"

Napi::Boolean wrap_AcquireVJD(const Napi::CallbackInfo& info);

void wrap_RelinquishVJD(const Napi::CallbackInfo& info);

Napi::Boolean wrap_ResetVJD(const Napi::CallbackInfo& info);

Napi::Boolean wrap_ResetButtons(const Napi::CallbackInfo& info);

Napi::Boolean wrap_ResetPovs(const Napi::CallbackInfo& info);

Napi::Boolean wrap_SetAxis(const Napi::CallbackInfo& info);

Napi::Boolean wrap_SetBtn(const Napi::CallbackInfo& info);

Napi::Boolean wrap_SetDiscPov(const Napi::CallbackInfo& info);

Napi::Boolean wrap_SetContPov(const Napi::CallbackInfo& info);