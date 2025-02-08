#include "../render_api.h"

#include <gl/GL.h>

class OpenGL : public IRenderAPI {
private:
    void createVBO();
    void createVAO();
    
public:
    HlResult init(GLFWwindow* window) override;
    void destroy() override;
    void startFrame() override;
    void endFrame() override;
    void clearScreen(Color color = COLOR_WHITE);
};
