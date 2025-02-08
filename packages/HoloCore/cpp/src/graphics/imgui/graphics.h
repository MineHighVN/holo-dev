#include "../draw.h"

#include <imgui/imgui.h>

class ImGuiGraphics : public IDraw {
private:
    ImDrawList* draw_list;

public:
    void drawRectangle(Vec2f begin, Vec2f end, float rounded = 0.0f, bool filled = false, Color color = COLOR_BLACK) override;
    void setDrawList(ImDrawList* draw_list);
    void drawText(std::string text, Vec2f position, Color color = COLOR_BLACK) override;
    // Calculate text size
    Vec2f calcTextSize(std::string text) override;
};
