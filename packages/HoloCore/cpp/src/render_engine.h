#pragma once

#include <string>
#include "render_api/vulkan/vulkan.h"
#include "render_api/opengl/opengl.h"
#include "render_api/render_api.h"
#include "graphics/color.h"
#include "graphics/vec.h"

#include "graphics/imgui/graphics.h"

class RenderEngine {
private:
    render_api renderAPI;

    Vulkan* vulkan = nullptr;
    OpenGL* opengl = nullptr;

    IRenderAPI* render = nullptr;

    GLFWwindow* window = nullptr;

    ImGuiGraphics* imguiGraphics = nullptr;

    IDraw* graphics;

public:
    RenderEngine(GLFWwindow* window, render_api renderAPI);
    ~RenderEngine();
    void startFrame();
    void clearScreen(Color color = COLOR_WHITE);
    void endFrame();
    IDraw* getDrawGraphics();
    HlResult init();
};
