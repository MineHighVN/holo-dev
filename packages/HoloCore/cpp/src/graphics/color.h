#pragma once

#include <string>

struct ColorNormalize {
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    float a = 1.0f;
};

struct Color {
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned char a = 255;

    ColorNormalize normalization();
};

extern Color COLOR_BLACK;
extern Color COLOR_WHITE;
extern Color COLOR_TRANSPARENT;

Color colorFromHex(unsigned int hex);
Color colorFromHex(const std::string& hex);
