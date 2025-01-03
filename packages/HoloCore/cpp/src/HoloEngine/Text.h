#pragma once

#include "Node.h"

class Text : public Node {
public:
    Text() : Node("text") {};
    void render() override;
};
