#include "Node.h"

#include "../utils/split.h"

HOLO_Attributes document;

std::atomic<uint64_t> Node::nextID = 1;
std::map<uint64_t, std::shared_ptr<Node>> NodeMap;

Node::Node(std::string nodeName) {
    this->NodeID = nextID++;
    this->nodeName = nodeName;
}

Node::~Node() {
    std::cout << "CleanUP ID >>> " << this->NodeID << "\n";
}

void Node::render() {
    this->height = 0;
    this->width = 0;

    // if (this->parent != nullptr) {
    //     this->parent->height = 0;
    //     this->parent->width = 0;
    // }

    for (const auto& child_cp : this->children) {
        if (std::holds_alternative<std::string>(child_cp)) {
            std::string child = std::get<std::string>(child_cp);
            int top = 0;
            int left = 0;

            const float initialDrawX = 10;
            const float initialDrawY = this->parent != nullptr ? this->parent->height : 0;

            float drawX = initialDrawX;
            float drawY = initialDrawY;

            float width = 0;
            float height = 0;

            ImVec2 space_size = ImGui::CalcTextSize(" ");

            std::vector<std::string> child_split = utils::split(child, ' ');

            float temp_width = 0;
            bool newLine = true;
            bool initial = true;

            for (std::string text : child_split) {
                if (newLine) {
                    drawX = initialDrawX;
                    float addHeight = space_size.y;
                    height += addHeight;
                    if (!initial)
                        drawY += addHeight;
                    else 
                        initial = false;
                    newLine = false;
                    temp_width = 0;
                }

                ImVec2 text_size = ImGui::CalcTextSize(text.c_str());

                this->DrawText(text, drawX, drawY, IM_COL32(0, 0, 0, 255));

                if (this->maxWidth != 0 && temp_width + text_size.x > this->maxWidth) {
                    width = std::max(width, temp_width);
                    newLine = true;
                } else {
                    float addWidth = text_size.x + space_size.x;
                    temp_width += addWidth;
                    drawX += addWidth;
                }
            }

            if (this->parent != nullptr) {
                this->height = height;
                this->parent->height += height;
                // std::cout << this->height << " " << this->parent->height << "\n";
            }
        } else {
            std::shared_ptr<Node> child = std::get<std::shared_ptr<Node>>(child_cp);
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

std::shared_ptr<Node> Node::getNode(uint64_t nodeId) {
    auto it = NodeMap.find(nodeId);
    if (it != NodeMap.end()) {
        return it->second;
    } else {
        std::cerr << "Node not found for the given key: " << nodeId << std::endl;
        return nullptr;
    }
}

void Node::appendChildren (holo_child child) {
    if (std::holds_alternative<std::string>(child)) {
        std::string children_cp = std::get<std::string>(child);

        child = children_cp;
    } else {
        holo_node children_cp = std::get<holo_node>(child);

        children_cp->parent = this->selfSharedAddress;
        
        child = children_cp;
    }

    this->children.push_back(child);
}

void Node::setChildren (holo_nodes children) {
    this->children = children;
}

void Node::setSelfSharedPtr (holo_node node) {
    if (this->selfSharedAddress == nullptr) {
        this->selfSharedAddress = node;
    } else {
        std::cerr << "self shared address already defined\n";
    }
}
