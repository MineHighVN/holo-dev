#include "vulkan.h"

#include <hLog.h>

#include <iostream>

HlResult Vulkan::init(GLFWwindow* window) {
    logger::verbose("setup vulkan render");
    logger::verbose("initialize vkDevice");
    this->window = window;
    this->context = new VulkanContext();
    this->context->createContext(window);
    return HL_SUCCESS;
}

void Vulkan::destroy() {
    delete this->context;
}

void Vulkan::clearScreen(int x, int y, unsigned int width, unsigned int height, Color color) {
    // VkClearColorValue clearColor = {};
    // clearColor.float32[0] = color.r / 255.0f;
    // clearColor.float32[1] = color.g / 255.0f;
    // clearColor.float32[2] = color.b / 255.0f;
    // clearColor.float32[3] = color.a / 255.0f;

    // VkClearAttachment clearAttachment = {};
    // clearAttachment.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    // clearAttachment.clearValue.color = clearColor;

    // VkClearRect clearRect = {};
    // clearRect.rect.offset = { x, y };
    // clearRect.rect.extent = { width, height };
    // clearRect.layerCount = 1;

    // vkCmdClearAttachments(this->context->commandBuffer, 1, &clearAttachment, 1, &clearRect);
}

void Vulkan::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) {
    VkCommandBufferBeginInfo beginInfo = {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = 0;
    beginInfo.pInheritanceInfo = nullptr;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    int width;
    int height;
    glfwGetWindowSize(this->window, &width, &height);

    VkClearValue clearColor = { {{255.0f, 255.0f, 255.0f, 1.0f}} };

    VkRenderPassBeginInfo renderPassBeginInfo = {};
    renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassBeginInfo.renderPass = this->context->renderpass;
    renderPassBeginInfo.framebuffer = this->context->framebuffers[imageIndex];
    renderPassBeginInfo.renderArea.offset = { 0, 0 };
    renderPassBeginInfo.renderArea.extent = this->context->getSwapChainExtent();
    renderPassBeginInfo.clearValueCount = 1;
    renderPassBeginInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(commandBuffer, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, this->context->graphicsPipeline);

    VkExtent2D swapchainExtent = this->context->getSwapChainExtent();

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(swapchainExtent.width);
    viewport.height = static_cast<float>(swapchainExtent.height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);
    VkRect2D scissor{};
    scissor.offset = {0, 0};
    scissor.extent = swapchainExtent;
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);
}

void Vulkan::startFrame() {
    vkWaitForFences(this->context->device, 1, &this->context->inFlightFence, VK_TRUE, UINT64_MAX);

    vkResetCommandBuffer(this->context->commandBuffer, 0);

    VkResult result = vkAcquireNextImageKHR(this->context->device, this->context->swapchain, UINT64_MAX, this->context->imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);
    if (result != VK_SUCCESS) {
        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            this->context->recreateSwapchain();
            
            result = vkAcquireNextImageKHR(this->context->device, this->context->swapchain, UINT64_MAX, this->context->imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);
            if (result != VK_SUCCESS) {
                throw std::runtime_error("failed to acquire next image.");
            }
        } else
            throw std::runtime_error("failed to acquire next image.");
    }

    vkResetFences(this->context->device, 1, &this->context->inFlightFence);

    this->recordCommandBuffer(this->context->commandBuffer, imageIndex);
}

void Vulkan::endFrame() {
    VkResult result;

    vkCmdEndRenderPass(this->context->commandBuffer);
    vkEndCommandBuffer(this->context->commandBuffer);

    VkSemaphore signalSemaphores[] = {this->context->renderFinishedSemaphore};

    VkSemaphore waitSemaphores[] = {this->context->imageAvailableSemaphore};

    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &this->context->commandBuffer;
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;

    VkResult submitResult = vkQueueSubmit(this->context->graphicsQueue, 1, &submitInfo, this->context->inFlightFence);
    if (submitResult != VK_SUCCESS) {
        throw std::runtime_error("Failed to submit draw command buffer.");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    VkSwapchainKHR swapChains[] = {this->context->swapchain};

    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = &this->context->swapchain;
    presentInfo.pWaitSemaphores = nullptr;
    presentInfo.waitSemaphoreCount = 0; 
    presentInfo.pImageIndices = &imageIndex;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    vkQueuePresentKHR(this->context->presentQueue, &presentInfo);
}

Vulkan::~Vulkan() {
    this->destroy();
}
