#include "Window.h"

#include <hLog.h>

#include <chrono>
#include <thread>

#include "../HoloEngine/Body.h"

#include "../HoloEngine/Node.h"

#include "../HPC/HPC.h"

#include "../render_api/vulkan/vulkan.h"

#ifdef _WIN32
const std::string OS_NAME = "Windows";
#elif __linux__
const std::string OS_NAME = "Linux";
#else
const std::string OS_NAME = "Unknown";
#endif

std::unique_ptr<Window> window;

bool Window::Init() {
    logger::verbose("OS Name: ", OS_NAME);

    if (!glfwInit()) {
        logger::error("failed to initialize glfw");
        return false;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    this->window = glfwCreateWindow(1280, 720, "HoloJS - New Project", NULL, NULL);
    if (!this->window) {
        glfwTerminate();
        return false;
    }

    try {
        this->renderEngine = new RenderEngine(this->window, API_VULKAN);
    } catch (const std::runtime_error& err) {
        logger::error(err.what());
        return false;
    }

    glfwMakeContextCurrent(this->window);
    // glfwSwapInterval(1);

    return true;
}

void Window::Render() {
    const float targetFrameTime = 1.0f / 30.0f;

    auto previousTime = std::chrono::high_resolution_clock::now();

    while (!glfwWindowShouldClose(this->window)) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> deltaTime = currentTime - previousTime;
        previousTime = currentTime;

        // if (deltaTime.count() < targetFrameTime) {
        //     std::this_thread::sleep_for(std::chrono::duration<float>(targetFrameTime - deltaTime.count()));
        // }
        
        glfwPollEvents();

        glfwGetWindowSize(this->window, &this->wWidth, &this->wHeight);

        if (!this->wWidth || !this->wHeight) continue;

        this->renderEngine->startFrame();
        this->renderEngine->clearScreen();

        if (body != nullptr) {
            body->render();
        }

        this->renderEngine->endFrame();

        glfwSwapBuffers(this->window);
    }
}

void Window::Quit() {
    this->renderEngine->~RenderEngine();

    glfwDestroyWindow(this->window);
    glfwTerminate();

    HPC::Emit("window_action", "close");
    delete this->vulkan;
}

void Window::setTitle(const char* title) {
    glfwSetWindowTitle(this->window, title);
}

GLFWwindow* Window::getGLFWWindow() {
    return this->getGLFWWindow();
}

RenderEngine *Window::getRenderEngine() {
    return this->renderEngine;
}

int Window::getWidth() {
    return this->wWidth;
}

int Window::getHeight() {
    return this->wHeight;
}
