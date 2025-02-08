#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "../types/HlResult.h"
#include "../graphics/color.h"

#include <imgui/imgui.h>

// Render API using by application
enum render_api {
    API_VULKAN, // Vulkan rendering is not working currently, please use OpenGL instend
    API_DIRECTX_11, // DirectX 11 rendering is not support, please use OpenGL instend
    API_OPENGL,
};

class IRenderAPI {
private:
    ImDrawList* draw_list = nullptr;
public:
    HlResult virtual init(GLFWwindow* window) = 0;
    void virtual destroy() = 0;
    void virtual startFrame() = 0;
    void virtual endFrame() = 0;
};
