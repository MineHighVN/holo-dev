#include "../draw.h"

#include "../vec.h"

class OpenGLGraphics : public IDraw {
public:
    void drawRectangle(Vec2f begin, Vec2f end, float rounded = 0.0f, bool filled = false, Color color = COLOR_WHITE) override;
    void drawText(std::string text, Vec2f position, Color color = COLOR_WHITE);
};
