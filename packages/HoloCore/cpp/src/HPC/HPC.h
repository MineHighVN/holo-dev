#pragma once

#include <iostream>
#include <node_api.h>

namespace HPC {
    extern napi_env global_env;
    extern napi_value global;

    napi_value ConvertToNapiValue(napi_env env, auto data);
    napi_value RegisterHPC(napi_env env, napi_callback_info info);
    void Emit(const char* event_name, std::string data);
}
