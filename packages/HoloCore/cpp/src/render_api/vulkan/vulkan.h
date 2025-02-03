#pragma once

#include "../render_api.h"
#include "context.h"

#include <memory>

class Vulkan : public IRenderAPI {
private:
    VulkanContext* context;
    GLFWwindow* window;
    uint32_t imageIndex;
    
public:
    void init(GLFWwindow* window) override;
    void drawRectangle(int x, int y, int width, int height, Color color = COLOR_BLACK, float rounded = 0.0f) override;
    void startFrame() override;
    void endFrame() override;
    void destroy() override;
    void clearScreen(int x, int y, unsigned int width, unsigned int height, Color color = COLOR_BLACK);
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    ~Vulkan();
};
