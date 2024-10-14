#ifndef RENDER_PIPELIONE_HEADERS
#define RENDER_PIPELIONE_HEADERS
#include "structs.h"
#include "vk_tools.h"
#include "debug.h"

void createRenderPass(struct Engine_App *state);
void createGraphicsPipeline(struct Engine_App *state);
void createFramebuffers(struct RazSwapChain* swapChain, VkDevice device, VkRenderPass renderPass); 
void createVertexBuffer(struct Engine_App *state);
void createIndexBuffer(struct Engine_App *state);
VkShaderModule createShaderModule(VkDevice device,const std::vector<char>& code);


#endif // !RENDER_PIPELIONE_HEADERS
