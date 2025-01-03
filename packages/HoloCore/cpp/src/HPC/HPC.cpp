#include "HPC.h"
#include <mutex>

namespace HPC {
    napi_ref callbackRef;
    napi_env global_env;
    napi_value global;
    napi_threadsafe_function tsfn;

    napi_value ConvertToNapiValue(napi_env env, auto data) {
        napi_value napiData;

        if constexpr (std::is_same_v<decltype(data), int>) {
            napi_create_int32(env, data, &napiData);
        } else if constexpr (std::is_same_v<decltype(data), double>) {
            napi_create_double(env, data, &napiData);
        } else if constexpr (std::is_same_v<decltype(data), bool>) {
            napi_get_boolean(env, data, &napiData);
        } else if constexpr (std::is_same_v<decltype(data), std::string>) {
            napi_create_string_utf8(env, data.c_str(), NAPI_AUTO_LENGTH, &napiData);
        } else if constexpr (std::is_same_v<decltype(data), const char*>) {
            napi_create_string_utf8(env, data, NAPI_AUTO_LENGTH, &napiData);
        } else {
            std::cerr << "DataType not supported\n";
            napi_get_undefined(env, &napiData);
        }

        return napiData;
    }

    napi_value RegisterHPC(napi_env env, napi_callback_info info) {
        size_t argc = 1;
        napi_value args[1];
        napi_get_cb_info(env, info, &argc, args, NULL, NULL);
        
        napi_status status = napi_create_reference(env, args[0], 1, &callbackRef);
        if (status != napi_ok) {
            std::cerr << "Failed to create reference to callback\n";
        }

        global_env = env;
        napi_get_global(env, &global);

        napi_value work_name;
        napi_create_string_utf8(env, "EmitWork", NAPI_AUTO_LENGTH, &work_name);

        status = napi_create_threadsafe_function(
            env,
            args[0],
            NULL,
            work_name,
            0,
            1,
            NULL,
            NULL,
            NULL,
            [](napi_env env, napi_value js_callback, void* context, void* data) {
                auto* emit_data = static_cast<std::pair<std::string, std::string>*>(data);
                napi_value args[2];
                napi_create_string_utf8(env, emit_data->first.c_str(), NAPI_AUTO_LENGTH, &args[0]);
                napi_create_string_utf8(env, emit_data->second.c_str(), NAPI_AUTO_LENGTH, &args[1]);
                napi_value result;
                napi_call_function(env, global, js_callback, 2, args, &result);
                delete emit_data;
            },
            &tsfn
        );

        if (status != napi_ok) {
            std::cerr << "Failed to create threadsafe function\n";
        }

        return NULL;
    }

    void Emit(const char* name, std::string data) {
        auto* emit_data = new std::pair<std::string, std::string>(name, data);

        napi_status status = napi_call_threadsafe_function(
            tsfn,
            emit_data,
            napi_tsfn_blocking
        );

        if (status != napi_ok) {
            std::cerr << "Failed to call threadsafe function\n";
            delete emit_data;
        }
    }
}