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
}
