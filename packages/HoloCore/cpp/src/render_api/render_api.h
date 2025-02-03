#pragma once

#include <GLFW/glfw3.h>

#include <GLFW/glfw3.h>
#include <iostream>

#include "../graphics/color.h"

// Render API using by application
enum render_api {
    API_VULKAN,
    API_DIRECTX_11,
    API_OPENGL,
};

class IRenderAPI {
public:
    void virtual init(GLFWwindow* window) = 0;
    void virtual destroy() = 0;
    void virtual startFrame() = 0;
    void virtual endFrame() = 0;
    virtual void drawRectangle(int x, int y, int width, int height, Color color, float rounded) = 0;
};
