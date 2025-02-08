#pragma once

#include "../graphics/color.h"

class StyleSheet {
    // Margin
    float marginTop = 0;
    float marginBottom = 0;
    float marginLeft = 0;
    float marginRight = 0;
    
    // Size
    float maxWidth = 0;
    float maxHeight = 0;

    // Border
    float borderLeft = 0;
    float borderRight = 0;
    float borderTop = 0;
    float borderBottom = 0;

    Color colorBorderLeft = COLOR_TRANSPARENT;
    Color colorBorderRight = COLOR_TRANSPARENT;
    Color colorBorderTop = COLOR_TRANSPARENT;
    Color colorBorderBottom = COLOR_TRANSPARENT;
};
