#pragma once

#define GLFW_INCLUDE_VULKAN

#include <iostream>
#include <GLFW/glfw3.h>
#include <memory>
#include "../render_engine.h"

class Window {
private:
    GLFWwindow* window;
    RenderEngine* renderEngine;
    Vulkan* vulkan;
    int wWidth = 0;
    int wHeight = 0;

public:
    bool Init();
    void Render();
    void Quit();
    void setTitle(const char* value);
    GLFWwindow* getGLFWWindow();
    RenderEngine* getRenderEngine();
    int getWidth();
    int getHeight();
};


extern std::unique_ptr<Window> window;
