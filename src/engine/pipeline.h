#pragma once
#include "vk_tools.h"

void createCommandPool(struct Engine_App *state);
void createCommandBuffers(struct Engine_App *state);
void createSyncObjects(struct Engine_App *state);


// Commands on loop
void recordCommandBuffer(struct Engine_App *state,VkCommandBuffer commandBuffer, uint32_t imageIndex);

void createRenderPass(struct Engine_App* state);
void createGraphicsPipeline(struct Engine_App* state);
void createFramebuffers(struct RazSwapChain* swapChain, VkDevice device, VkRenderPass renderPass);
void createVertexBuffer(struct Engine_App* state);
void createIndexBuffer(struct Engine_App* state);
void createUniformBuffer(struct Engine_App* state);
VkShaderModule createShaderModule(VkDevice device, const std::vector<char>& code);

void updateUniformBuffer(struct Engine_App* state, uint32_t currentImage);
void createDescriptorSetLayout(struct Engine_App* state);
void createDescriptorPool(struct Engine_App* state);
void createDescriptorSets(struct Engine_App* state);


void createSwapChain(struct RazWindow* window, struct RazSwapChain* swapChain);
void createImageViews(struct RazWindow* window, struct RazSwapChain* swapChain);

VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
VkExtent2D chooseSwapExtent(GLFWwindow *window,const VkSurfaceCapabilitiesKHR& capabilities);
void recreateSwapChain(struct Engine_App* state);
void cleanupSwapChain(RazSwapChain *swapChain,VkDevice device );

