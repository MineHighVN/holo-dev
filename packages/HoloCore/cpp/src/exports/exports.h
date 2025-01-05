#pragma once

#include <node_api.h>
#include <string>

namespace exports {
    void exportFunction (napi_env env, std::string name, napi_value obj, napi_callback cb);
    void exports (napi_env env, napi_value obj);
}
