#pragma once

#include <string>
#include "render_api/vulkan/vulkan.h"
#include "render_api/render_api.h"
#include "graphics/color.h"
#include "graphics/vec.h"

class RenderEngine {
private:
    render_api renderAPI;

    Vulkan* vulkan = nullptr;
    IRenderAPI* render = nullptr;

    GLFWwindow* window = nullptr;

public:
    RenderEngine(GLFWwindow* window, render_api renderAPI);
    ~RenderEngine();
    void startFrame();
    void clearScreen(Color color = COLOR_WHITE);
    void endFrame();
};
