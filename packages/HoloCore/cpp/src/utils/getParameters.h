#include <node_api.h>
#include <iostream>
namespace utils {
    std::string getString (napi_env env, napi_value value);
    uint64_t getUint64 (napi_env env, napi_value value);
}