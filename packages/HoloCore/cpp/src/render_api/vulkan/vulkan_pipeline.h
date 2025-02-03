#include "../Pipeline.h"

#include <vulkan/vulkan.h>
#include <string>

class VulkanPipeline : public Pipeline {
public:
    VkPipeline createGraphicsPipeline(VkDevice device, VkRenderPass renderpass, VkExtent2D swapChainExtent, const std::string &vertFilepath, const std::string &fragFilepath);
    VkShaderModule createShaderModule(VkDevice device, std::vector<char>& code);
    std::vector<VkFramebuffer> createFramebuffers(VkDevice device, VkRenderPass renderPass, const std::vector<VkImageView>& swapChainImageViews, VkExtent2D swapChainExtent);
};
