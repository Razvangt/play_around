#ifndef RAZ_VK_COMMANDS_HEADERS
#define RAZ_VK_COMMANDS_HEADERS
#include "structs.h"
#include "vk_tools.h"
// Commands 
void createCommandPool(struct Engine_App *state);
void createCommandBuffers(struct Engine_App *state);
void createSyncObjects(struct Engine_App *state);


// Commands on loop
void recordCommandBuffer(struct Engine_App *state,VkCommandBuffer commandBuffer, uint32_t imageIndex);


#endif // !RAZ_VK_COMMANDS_HEADERS
