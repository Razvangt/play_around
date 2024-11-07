#pragma once
#include "debug.h"
#include "structs.h"
#include "vk_tools.h"


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


