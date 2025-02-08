#include "graphics.h"

#include <iostream>

void ImGuiGraphics::drawRectangle(Vec2f begin, Vec2f end, float rounded, bool filled, Color color) {
    
}

void ImGuiGraphics::setDrawList(ImDrawList* draw_list) {
    this->draw_list = draw_list;
}

void ImGuiGraphics::drawText(std::string text, Vec2f position, Color color) {
    this->draw_list->AddText(ImVec2{position.x, position.y}, IM_COL32(color.r, color.g, color.b, color.a), text.c_str());
}

Vec2f ImGuiGraphics::calcTextSize(std::string text)
{
    ImVec2 size = ImGui::CalcTextSize(text.c_str());

    return Vec2f{ size.x, size.y };
}
