#pragma once

#include "color.h"
#include "vec.h"

class IDraw {
public:
    virtual void drawRectangle(Vec2f begin, Vec2f end, float rounded = 0.0f, bool filled = false, Color color = COLOR_BLACK) = 0;
    virtual void drawText(std::string text, Vec2f position, Color color = COLOR_BLACK) = 0;
    virtual Vec2f calcTextSize(std::string text) = 0;
};
