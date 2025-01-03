#pragma once

#include <iostream>
#include <GLFW/glfw3.h>
#include <memory>
#include <imgui/imgui.h>

class Window {
private:
    GLFWwindow* window;
public:
    bool Init();
    void Render();
    void Quit();
    void setTitle(const char* value);
    GLFWwindow* getGLFWWindow();
    ImDrawList* draw_list = nullptr;
};


extern std::unique_ptr<Window> window;
