#pragma once

#include <vulkan/vulkan.h>
#include <string>
#include <GLFW/glfw3.h>
#include <vector>

struct QueueFamilyIndices {
    int graphicsFamily = -1;
    int presentFamily = -1;
};

class VulkanContext {
private:
    GLFWwindow* window;

    VkInstance createInstance(const char* appName);
    VkSurfaceKHR createSurface();
    VkPhysicalDevice pickPhysicalDevice();
    QueueFamilyIndices findQueueFamilies();
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
    void createContext(GLFWwindow* window);
    void recreateSwapchain();
};
