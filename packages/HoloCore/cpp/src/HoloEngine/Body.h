#pragma once

#include "Node.h"
#include <memory.h>

class Body : public Node {
public:
    Body() : Node("body") {};
    void render() override;
};

extern std::shared_ptr<Body> body;
