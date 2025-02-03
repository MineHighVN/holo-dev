#include "render_engine.h"
#include "errors/render_engine_errors.h"

RenderEngine::RenderEngine(GLFWwindow* window, render_api renderAPI) {
    this->renderAPI = renderAPI;
    this->window = window;

    if (renderAPI == API_VULKAN) {
        this->vulkan = new Vulkan();
        this->render = this->vulkan;
    }

    this->render->init(window);
}

RenderEngine::~RenderEngine() {
    delete this->render;
}

void RenderEngine::startFrame() {
    this->render->startFrame();
}

void RenderEngine::clearScreen(Color color) {
    int width = 0;
    int height = 0;

    glfwGetWindowSize(this->window, &width, &height);

    if (this->renderAPI == API_VULKAN) {
        this->vulkan->clearScreen(0, 0, width, height, color);
        return;
    }
}

void RenderEngine::endFrame() {
    this->render->endFrame();
}
