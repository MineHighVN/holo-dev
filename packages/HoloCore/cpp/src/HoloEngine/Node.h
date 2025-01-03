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
    unsigned short clientWidth = 0;
    unsigned short clientHeight = 0;

    unsigned int scrollX = 0;
    unsigned int scrollY = 0;

    float top = 0.0f;
    float bottom = 0.0f;
    float left = 0.0f;
    float right = 0.0f;
};

class Node;

using holo_nodes = std::vector<std::shared_ptr<Node>>;
using holo_children = std::variant<holo_nodes, std::string, std::nullptr_t>;

class Node : public HOLO_Attributes {
private:
    static std::atomic<unsigned int> nextID;
    std::string nodeName;
protected:
    void DrawLine(float x1, float y1, float x2, float y2, ImU32 col, float thickness = 1.0f);
    void DrawText(std::string text, float x, float y, ImU32 col);
    unsigned int NodeID;
public:
    Node(std::string nodeName);
    ~Node();
    StyleSheet style;
    virtual void render() = 0;
    Node* parent = nullptr;
    unsigned int getNodeID() const;
    std::string getNodeName ();
    holo_children children = nullptr;
};

extern HOLO_Attributes body;
extern std::map<unsigned int, std::shared_ptr<Node>> NodeMap;
