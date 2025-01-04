#include "Node.h"

HOLO_Attributes document;

std::atomic<unsigned int> Node::nextID = 1;
std::map<unsigned int, std::shared_ptr<Node>> NodeMap;

Node::Node(std::string nodeName) {
    this->NodeID = nextID++;
    this->nodeName = nodeName;
}

Node::~Node() {
    std::cout << "CleanUP ID >>> " << this->NodeID << "\n";
}

void Node::renderChildren() {
    if (std::holds_alternative<holo_nodes>(children)) {
        holo_nodes& children = std::get<holo_nodes>(this->children);

        for (const auto& child : children) {
            child->render();
        }
    }
}

void Node::DrawLine(float x1, float y1, float x2, float y2, ImU32 col, float thickness) {
    window->draw_list->AddLine(ImVec2{ x1, y1 }, ImVec2{ x2, y2 }, col, thickness);
}

void Node::DrawText(std::string text, float x1, float x2, ImU32 col) {
    window->draw_list->AddText(ImVec2{x1, x2}, col, text.c_str());
}

unsigned int Node::getNodeID () const {
    return this->NodeID;
}

std::string Node::getNodeName() {
    return this->nodeName;
}
