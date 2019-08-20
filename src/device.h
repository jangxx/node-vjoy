#pragma once

#include "napi.h"
#include "../include/stdafx.h"
#include "../include/public.h"
#include "../include/vjoyinterface.h"

Napi::Number wrap_GetVJDButtonNumber(const Napi::CallbackInfo& info);

Napi::Number wrap_GetVJDDiscPovNumber(const Napi::CallbackInfo& info);

Napi::Number wrap_GetVJDContPovNumber(const Napi::CallbackInfo& info);

Napi::Boolean wrap_GetVJDAxisExists(const Napi::CallbackInfo& info);

Napi::String wrap_GetVJDStatus(const Napi::CallbackInfo& info);

Napi::Boolean wrap_isVJDExists(const Napi::CallbackInfo& info);