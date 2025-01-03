#include<node_api.h>
#include <thread>
#include <memory>
#include <condition_variable>
#include <mutex>

#include "Window/Window.h"
#include "utils/getParameters.h"
#include "HPC/HPC.h"
#include "HoloEngine/NodeManager.h"
#include "HoloEngine/Node.h"

napi_value setTitle(napi_env env, napi_callback_info info) {
    napi_value args[1];
    napi_value results;
    size_t argc = 1;
    napi_status status;

    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    window->setTitle(utils::getString(env, args[0]).c_str());

    return 0;
}

napi_value createNode(napi_env env, napi_callback_info info) {
    napi_value args[1];
    napi_value results;
    size_t argc = 1;
    napi_status status;

    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    unsigned int id = NodeManager::CreateNode(utils::getString(env, args[0]));

    napi_value result;

    napi_create_int64(env, id, &result);

    return result;
}

napi_value setChildren(napi_env env, napi_callback_info info) {
    napi_value args[2];
    size_t argc = 2;
    napi_status status;

    napi_get_cb_info(env, info, &argc, args, NULL, NULL);

    napi_valuetype arg1Type;
    status = napi_typeof(env, args[1], &arg1Type);
    if (status != napi_ok) {
        std::cerr << "Cannot get children dataType" << "\n";
        return nullptr;
    }

    int64_t nodeId;
    napi_get_value_int64(env, args[0], &nodeId);

    auto it = NodeMap.find((uint64_t)nodeId);
    if (it != NodeMap.end()) {
        if (arg1Type == napi_string) {
            std::shared_ptr<Node> node = it->second;

            node->children = utils::getString(env, args[1]);
        } else if (arg1Type == napi_number) {
            int64_t num;
            status = napi_get_value_int64(env, args[1], &num); 
            if (status != napi_ok) {
                napi_throw_type_error(env, nullptr, "Failed to get int64 value");
                return nullptr;
            }

            if (num < 0) {
                napi_throw_type_error(env, nullptr, "Value cannot be negative for uint64_t");
                return nullptr;
            }

            uint64_t uintNum = static_cast<uint64_t>(num); 
        } else {
            napi_throw_type_error(env, nullptr, "Expected string or number as the first argument");
            return nullptr;
        }
    } else {
        std::cerr << "Node not found for the given key: " << nodeId << std::endl;
        return nullptr;
    }

    return 0;
}

napi_value initWindow (napi_env env, napi_callback_info info) {
    window = std::make_unique<Window>();

    std::mutex mtx;
    std::condition_variable cv;
    bool init_done = false;

    std::thread HandleThread([&] {
        bool success = window->Init();

        {
            std::lock_guard<std::mutex> lock(mtx);
            init_done = true;
        }
        cv.notify_one();

        if (success) {
            window->Render();
            window->Quit();

        }
    });

    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&] { return init_done; });
    }

    HandleThread.detach();

    return 0;
}

napi_value init(napi_env env, napi_value exports) {
    napi_value windowObj;
    napi_create_object(env, &windowObj);

    napi_value hpcObj;
    napi_create_object(env, &hpcObj);

    napi_value documentObj;
    napi_create_object(env, &documentObj);

    napi_value window_setTitle;
    napi_value window_init;
    napi_value hpc_registerHPC;
    napi_value main_createNode;
    napi_value document_setChildren;

    napi_create_function(env, "setTitle", NAPI_AUTO_LENGTH, setTitle, nullptr, &window_setTitle);
    napi_create_function(env, "init", NAPI_AUTO_LENGTH, initWindow, nullptr, &window_init);

    napi_create_function(env, "registerHPC", NAPI_AUTO_LENGTH, HPC::RegisterHPC, nullptr, &hpc_registerHPC);

    napi_create_function(env, "createNode", NAPI_AUTO_LENGTH, createNode, nullptr, &main_createNode);

    napi_create_function(env, "setChildren", NAPI_AUTO_LENGTH, setChildren, nullptr, &document_setChildren);

    napi_set_named_property(env, windowObj, "setTitle", window_setTitle);
    napi_set_named_property(env, windowObj, "init", window_init);

    napi_set_named_property(env, hpcObj, "registerHPC", hpc_registerHPC);

    napi_set_named_property(env, documentObj, "setChildren", document_setChildren);

    napi_set_named_property(env, exports, "window", windowObj);
    napi_set_named_property(env, exports, "hpc", hpcObj);
    napi_set_named_property(env, exports, "document", documentObj);
    napi_set_named_property(env, exports, "createNode", main_createNode);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init);
