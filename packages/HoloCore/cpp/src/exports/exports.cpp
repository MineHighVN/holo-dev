#include "exports.h"

#include <mutex>
#include <thread>
#include <condition_variable>

#include "../Window/Window.h"
#include "../utils/getParameters.h"
#include "../HPC/HPC.h"
#include "../HoloEngine/NodeManager.h"
#include "../HoloEngine/Node.h"
#include "../utils/Translator.h"

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

    holo_node parent = Translator::getNode(env, args[0]);

    bool isArray = false;

    napi_is_array(env, args[1], &isArray);

    holo_nodes children;

    if (isArray) {
        uint32_t jsArraySize;

        napi_get_array_length(env, args[1], &jsArraySize);

        for (uint32_t i = 0; i < jsArraySize; i++) {
            napi_value element;

            napi_get_element(env, args[1], i, &element);

            napi_valuetype valuetype;
            napi_typeof(env, element, &valuetype);

            holo_child child;

            if (valuetype == napi_string) {
                child = utils::getString(env, element);
            } else if (valuetype == napi_object) {
                napi_value NodeIDAddr;

                napi_get_named_property(env, element, "NodeID", &NodeIDAddr);

                holo_node child_cp = Node::getNode(utils::getUint64(env, NodeIDAddr));

                child_cp->parent = parent;

                child = child_cp;
            } else {
                napi_throw_error(env, NULL, "not support datatype");
                return 0;
            }

            children.push_back(child);
        }
    } else {
        napi_valuetype valuetype;
        napi_typeof(env, args[1], &valuetype);

        holo_child child;

        if (valuetype == napi_string) {
            child = utils::getString(env, args[1]);
        } else if (valuetype == napi_object) {
            napi_value NodeIDAddr;

            napi_get_named_property(env, args[1], "NodeID", &NodeIDAddr);

            holo_node child_cp = Node::getNode(utils::getUint64(env, NodeIDAddr));

            child_cp->parent = parent;

            child = child_cp;
        } else {
            napi_throw_error(env, NULL, "not support datatype");
            return 0;
        }

        children.push_back(child);
    }

    parent->setChildren(children);

    return 0;
}

napi_value appendChildren(napi_env env, napi_callback_info info) {
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

    holo_node parent = Translator::getNode(env, args[0]);

    bool isArray = false;

    napi_is_array(env, args[1], &isArray);

    if (isArray) {
        uint32_t jsArraySize;

        napi_get_array_length(env, args[1], &jsArraySize);

        for (uint32_t i = 0; i < jsArraySize; i++) {
            napi_value element;

            napi_get_element(env, args[1], i, &element);

            napi_valuetype valuetype;
            napi_typeof(env, element, &valuetype);

            holo_child child;

            if (valuetype == napi_string) {
                child = utils::getString(env, element);
            } else if (valuetype == napi_object) {
                napi_value NodeIDAddr;

                napi_get_named_property(env, element, "NodeID", &NodeIDAddr);

                holo_node child_cp = Node::getNode(utils::getUint64(env, NodeIDAddr));

                child_cp->parent = parent;

                child = child_cp;
            } else {
                napi_throw_error(env, NULL, "not support datatype");
                return 0;
            }

            parent->appendChildren(child);
        }
    } else {
        napi_valuetype valuetype;
        napi_typeof(env, args[1], &valuetype);

        holo_child child;

        if (valuetype == napi_string) {
            child = utils::getString(env, args[1]);
        } else if (valuetype == napi_object) {
            napi_value NodeIDAddr;

            napi_get_named_property(env, args[1], "NodeID", &NodeIDAddr);
            
            holo_node child_cp = Node::getNode(utils::getUint64(env, NodeIDAddr));

            child_cp->parent = parent;

            child = child_cp;
        } else {
            napi_throw_error(env, NULL, "not support datatype");
            return 0;
        }

        parent->appendChildren(child);
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

namespace exports {
    void exportFunction (napi_env env, std::string name, napi_value obj, napi_callback cb) {
        napi_value result;

        napi_create_function(env, name.c_str(), NAPI_AUTO_LENGTH, cb, NULL, &result);

        napi_set_named_property(env, obj, name.c_str(), result);
    }

    void exports (napi_env env, napi_value obj) {
        napi_value windowObj;
        napi_create_object(env, &windowObj);

        napi_value hpcObj;
        napi_create_object(env, &hpcObj);

        napi_value documentObj;
        napi_create_object(env, &documentObj);

        {
            exportFunction(env, "setTitle", windowObj, setTitle);
            exportFunction(env, "init", windowObj, initWindow);

            exportFunction(env, "registerHPC", hpcObj, HPC::RegisterHPC);

            exportFunction(env, "createNode", documentObj, createNode);
            exportFunction(env, "appendChildren", documentObj, appendChildren);
            exportFunction(env, "setChildren", documentObj, setChildren);
        }
        
        napi_set_named_property(env, obj, "window", windowObj);
        napi_set_named_property(env, obj, "hpc", hpcObj);
        napi_set_named_property(env, obj, "document", documentObj);
    }
}
