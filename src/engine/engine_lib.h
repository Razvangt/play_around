#ifndef VK_APP_HEADDERS
#define VK_APP_HEADDERS
#include "structs.h"
#include "debug.h"
#include "vk_tools.h"
#include "window.h"
#include "swapchain.h"
#include "vk_commands.h"
#include "render_pipeline.h"

// Run Method 
void run(struct Engine_App *state);

// Vulkan set Up 
void initVulkan(struct Engine_App *state);

// Loop Methods
void mainLoop(struct Engine_App *state);
void drawFrame(struct Engine_App *state);

// Clean Methods 
void cleanup(struct Engine_App *state);

#endif // !VK_APP_HEADDERS
