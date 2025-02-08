#include "opengl.h"

#include <hLog.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

void OpenGL::createVBO() {}

void OpenGL::createVAO() {}

HlResult OpenGL::init(GLFWwindow* window) {
    // logger::info("detect opengl version: ", glGetString(GL_VERSION));
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return HL_FAILURE;
    }

    return HL_SUCCESS;
}

void OpenGL::destroy() {

}

void OpenGL::startFrame() {

}

void OpenGL::endFrame() {
    
}

void OpenGL::clearScreen(Color color) {
    auto colNormalize = color.normalization();
    glClearColor(colNormalize.r, colNormalize.g, colNormalize.b, colNormalize.a); 
    glClear(GL_COLOR_BUFFER_BIT);
}
