#include<node_api.h>
#include <thread>
#include <memory>
#include <condition_variable>
#include <iostream>

#include "exports/exports.h"

#include "utils/split.h"

napi_value init(napi_env env, napi_value exportsObj) {
    exports::exports(env, exportsObj);

    return exportsObj;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init);
