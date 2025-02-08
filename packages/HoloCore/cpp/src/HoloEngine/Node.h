#pragma once

#include "../StyleSheet/StyleSheet.h"
#include "../Window/Window.h"
#include <map>
#include <vector>
#include <memory>
#include <atomic>
#include <variant>
#include "../graphics/draw.h"

struct HOLO_Attributes {
    unsigned short height = 0;
    unsigned short width = 0;

    unsigned int scrollX = 0;
    unsigned int scrollY = 0;

    float maxWidth = 0;
    float maxHeight = 0;

    float top = 0.0f;
    float left = 0.0f;
};

class Node;

using holo_node = std::shared_ptr<Node>;
using holo_child = std::variant<std::string, holo_node>;
using holo_nodes = std::vector<holo_child>;

class Node : public HOLO_Attributes {
private:
    static std::atomic<uint64_t> nextID;
    std::string nodeName;
    holo_node selfSharedAddress = nullptr;

protected:
    void drawLine(Vec2f begin, Vec2f end, Color col, float thickness = 1.0f);
    void drawText(std::string text, Vec2f position);
    // Calculate text size
    Vec2f calcTextSize(std::string text);
    unsigned int NodeID;
    holo_nodes children;
    float drawPosX = 0;
    float drawPosY = 0;

    IDraw* graphics = nullptr;

public:
    Node(std::string nodeName);
    StyleSheet style;
    virtual void render();
    std::shared_ptr<Node> parent = nullptr;
    unsigned int getNodeID() const;
    std::string getNodeName();

    void appendChildren(holo_child children);
    void setChildren(holo_nodes children);
    void setSelfSharedPtr(holo_node node);
    void setDrawGraphics(IDraw* graphics);
    static std::shared_ptr<Node> getNode(uint64_t nodeId);
};

extern std::map<uint64_t, std::shared_ptr<Node>> NodeMap;
