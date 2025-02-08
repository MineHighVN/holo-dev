#include <glad/glad.h>
#include <glfw/glfw3.h>

class OpenGLContext {
private:
    GLuint VAO;
    GLuint VBO;

    void initVAO();
    void initVBO();

public:
    void createContext();
    void destroyContext();
};
