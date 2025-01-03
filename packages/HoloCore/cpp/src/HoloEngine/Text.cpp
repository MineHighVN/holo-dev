#include "Text.h"

void Text::render() {
    if (std::holds_alternative<std::string>(this->children)) {
        std::string text = std::get<std::string>(this->children);

        this->DrawText(text, 20, 10, IM_COL32(0, 0, 0, 255));
    }
}