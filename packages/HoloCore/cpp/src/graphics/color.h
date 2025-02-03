#pragma once

#include <string>

struct Color {
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned char a = 255;
};

extern Color COLOR_BLACK;
extern Color COLOR_WHITE;

Color ColorFromHex(unsigned int hex);
Color ColorFromHex(const std::string& hex);
