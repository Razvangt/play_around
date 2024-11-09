#pragma once
#include "vk_tools.h"
#include <unordered_map>

void createCommandPool(struct Engine_App* state);
void createCommandBuffers(struct Engine_App* state);
void createSyncObjects(struct Engine_App* state);
void createRenderPass(struct Engine_App* state);
void createGraphicsPipeline(struct Engine_App* state);
void createFramebuffers(struct RazSwapChain* swapChain, VkDevice device, VkRenderPass renderPass, VkImageView depthImageView);
void createVertexBuffer(struct Engine_App* state);
void createIndexBuffer(struct Engine_App* state);
void createUniformBuffer(struct Engine_App* state);
VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code);
void createDescriptorSetLayout(struct Engine_App* state);
void createDescriptorPool(struct Engine_App* state);
void createDescriptorSets(struct Engine_App* state);
void createSwapChain(struct RazWindow* window, struct RazSwapChain* swapChain);
void createImageViews(struct RazWindow* window, struct RazSwapChain* swapChain);
void createTextureImage(struct Engine_App* state);
void createTextureImageView(struct Engine_App* state);
void createTextureSampler(struct Engine_App* state);
void createDepthResources(struct Engine_App* state);
VkImageView createImageView(struct RazWindow* window, VkImage image, VkFormat format,VkImageAspectFlags aspectFlags);

void loadModel(struct Engine_App* state);


void recordCommandBuffer(struct Engine_App* state, VkCommandBuffer commandBuffer, uint32_t imageIndex);
void updateUniformBuffer(struct Engine_App* state, uint32_t currentImage);
VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
VkExtent2D chooseSwapExtent(GLFWwindow* window, const VkSurfaceCapabilitiesKHR& capabilities);
void recreateSwapChain(struct Engine_App* state);
void cleanupSwapChain(RazSwapChain* swapChain, VkDevice device);

void createImage(struct Engine_App* state,
uint32_t width,
uint32_t height,
VkFormat format,
VkImageTiling tiling,
VkImageUsageFlags usage,
VkMemoryPropertyFlags properties,
VkImage& image,
VkDeviceMemory& imageMemory);
