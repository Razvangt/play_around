#pragma  once
#include "structs.h"
#include "vk_tools.h"
// Commands 
void createCommandPool(struct Engine_App *state);
void createCommandBuffers(struct Engine_App *state);
void createSyncObjects(struct Engine_App *state);


// Commands on loop
void recordCommandBuffer(struct Engine_App *state,VkCommandBuffer commandBuffer, uint32_t imageIndex);


