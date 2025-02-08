#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <GLFW/glfw3.h>
#include <vector>

#include "../../types/HlResult.h"

struct QueueFamilyIndices {
    int graphicsFamily = -1;
    int presentFamily = -1;
};

class VulkanContext {
private:
    GLFWwindow* window;

    VkResult createInstance(const char* appName);
    VkResult createSurface();
    HlResult pickPhysicalDevice();
    HlResult findQueueFamilies();
    VkDevice createLogicalDevice();
    VkSwapchainKHR createSwapchain(VkExtent2D extent, uint32_t imageCount);
    VkRenderPass createRenderPass(VkFormat swapChainImageFormat);
    std::vector<VkImageView> createSwapChainImageViews();
    std::vector<VkFramebuffer> createFramebuffers();
    void createSyncObject();
    void cleanupSwapchain();
    void cleanupSyncObject();

public:
    VkInstance instance;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice;
    VkDevice device;
    QueueFamilyIndices indices;
    VkSwapchainKHR swapchain;
    VkRenderPass renderpass;
    VkSurfaceFormatKHR surfaceFormat;
    std::vector<VkImageView> swapchainImageViews;
    std::vector<VkFramebuffer> framebuffers;
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkPipeline graphicsPipeline;
    VkSemaphore imageAvailableSemaphore;
    VkSemaphore renderFinishedSemaphore;
    VkFence inFlightFence;

    VkExtent2D getSwapChainExtent();
    HlResult createContext(GLFWwindow* window);
    void recreateSwapchain();
};
