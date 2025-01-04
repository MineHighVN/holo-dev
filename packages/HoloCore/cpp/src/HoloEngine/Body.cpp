#include "Body.h"

void Body::render() {
    this->renderChildren();
}

std::shared_ptr<Body> body;
