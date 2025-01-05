#pragma once

#include <imgui/imgui.h>
#include "../StyleSheet/StyleSheet.h"
#include "../Window/Window.h"
#include <map>
#include <vector>
#include <memory>
#include <atomic>
#include <variant>

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
    void DrawLine(float x1, float y1, float x2, float y2, ImU32 col, float thickness = 1.0f);
    void DrawText(std::string text, float x, float y);
    unsigned int NodeID;
    holo_nodes children;
    float drawPosX = 0;
    float drawPosY = 0;
public:
    Node(std::string nodeName);
    ~Node();
    StyleSheet style;
    virtual void render();
    std::shared_ptr<Node> parent = nullptr;
    unsigned int getNodeID() const;
    std::string getNodeName ();

    void appendChildren(holo_child children);
    void setChildren(holo_nodes children);
    void setSelfSharedPtr(holo_node node);
    static std::shared_ptr<Node> getNode(uint64_t nodeId);
};

extern std::map<uint64_t, std::shared_ptr<Node>> NodeMap;
