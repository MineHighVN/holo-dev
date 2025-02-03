#include "color.h"
#include <sstream>

Color COLOR_BLACK{ 0, 0, 0, 255};
Color COLOR_WHITE{ 255, 255, 255, 255};

Color ColorFromHex(unsigned int hex) {
    Color color{};

    color.r = (hex >> 24) & 0xFF;
    color.g = (hex >> 16) & 0xFF;
    color.b = (hex >> 8) & 0xFF;
    color.a = hex & 0xFF;

    return color;
}

Color ColorFromHex(const std::string& hexStr) {
    std::string hex = hexStr;
    if (hex.size() == 4) {
        hex.insert(2, 1, hex[1]);
        hex.insert(4, 1, hex[2]);
    } else if (hex.size() == 5) {
        hex.insert(2, 1, hex[1]);
        hex.insert(4, 1, hex[2]);
        hex.insert(6, 1, hex[3]);
    }

    unsigned int hexValue;
    std::stringstream ss;
    if (hex.size() > 0 && hex[0] == '#')
        ss << std::hex << hex.substr(1);
    ss >> hexValue;

    return ColorFromHex(hexValue);
}
