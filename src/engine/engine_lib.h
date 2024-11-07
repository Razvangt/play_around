#pragma once
#include "window.h"
#include "pipeline.h"

// Run Method 
void run(struct Engine_App *state);

// Vulkan set Up 
void initVulkan(struct Engine_App *state);

// Loop Methods
void mainLoop(struct Engine_App *state);
void drawFrame(struct Engine_App *state);

// Clean Methods 
void cleanup(struct Engine_App *state);

