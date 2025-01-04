#include <node_api.h>
#include <iostream>
#include "getParameters.h"

namespace utils {
    std::string getString (napi_env env, napi_value value) {
        size_t title_len;
        napi_status status = napi_get_value_string_utf8(env, value, NULL, 0, &title_len);
        if (status != napi_ok) {
            napi_throw_error(env, NULL, "Invalid title parameter");
            return NULL;
        }


        char* title = (char*)malloc(title_len + 1);
        status = napi_get_value_string_utf8(env, value, title, title_len + 1, &title_len);
        if (status != napi_ok) {
            free(title);
            napi_throw_error(env, NULL, "Failed to get string value");
            return NULL;
        }

        return title;
    }

    uint64_t getUint64 (napi_env env, napi_value value) {
        int64_t num;
        napi_status status = napi_get_value_int64(env, value, &num); 
        if (status != napi_ok) {
            napi_throw_type_error(env, nullptr, "Failed to get int64 value");
            return -1;
        }

        if (num < 0) {
            napi_throw_type_error(env, nullptr, "Value cannot be negative for uint64_t");
            return -1;
        }

        uint64_t uintNum = static_cast<uint64_t>(num); 

        return uintNum;
    }
}
