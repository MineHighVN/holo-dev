#include "context.h"

#include <hLog.h>

void OpenGLContext::initVAO() {
    // glGenVertexArrays(1, &VAO);
    // glBindVertexArray(VAO);
}

void OpenGLContext::initVBO() {
    
}

void OpenGLContext::createContext() {
    logger::verbose("OpenGL version: ", (const char*)glGetString(GL_VERSION));

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        logger::error("Failed to initialize GLAD");
        glfwTerminate();
        return;
    }

    logger::verbose("init opengl vao");
    this->initVAO();
    logger::verbose("init opengl vbo");
    this->initVBO();
}

void OpenGLContext::destroyContext() {

}
