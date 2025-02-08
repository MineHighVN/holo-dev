#include "render_engine.h"
#include "errors/render_engine_errors.h"

#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

#include <hLog.h>

#define IMGUI_BACKEND true

RenderEngine::RenderEngine(GLFWwindow* window, render_api renderAPI) {
    this->renderAPI = renderAPI;
    this->window = window;

    if (renderAPI == API_VULKAN) {
        this->vulkan = new Vulkan();
        this->render = this->vulkan;
    }

    if (renderAPI == API_OPENGL) {
        this->opengl = new OpenGL();
        this->render = this->opengl;
    }

    if (IMGUI_BACKEND) {
        this->imguiGraphics = new ImGuiGraphics();
        this->graphics = this->imguiGraphics;
    }
}

HlResult RenderEngine::init() {
    return this->render->init(window);
}

RenderEngine::~RenderEngine() {
    this->render->destroy();

    if (IMGUI_BACKEND) {
        if (this->renderAPI == API_OPENGL)
            ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    delete this->graphics;
    delete this->render;
}

void RenderEngine::startFrame() {
    if (IMGUI_BACKEND) {
        if (this->renderAPI == API_OPENGL) {
            ImGui_ImplOpenGL3_NewFrame();
        }
        
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        this->imguiGraphics->setDrawList(ImGui::GetBackgroundDrawList());
    } else {
        this->render->startFrame();
    }
}

void RenderEngine::clearScreen(Color color) {
    int width = 0;
    int height = 0;

    glfwGetWindowSize(this->window, &width, &height);

    if (this->renderAPI == API_VULKAN) {
        this->vulkan->clearScreen(0, 0, width, height, color);
        return;
    }

    if (this->renderAPI == API_OPENGL) {
        this->opengl->clearScreen();
        return;
    }
}

void RenderEngine::endFrame() {
    if (IMGUI_BACKEND) {
        ImGui::Render();

        if (this->renderAPI == API_OPENGL)
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    } else {
        this->render->endFrame();
    }
}

IDraw* RenderEngine::getDrawGraphics() {
    return this->graphics;
}
