#ifndef RAZ_SWAPCHAIN_HEADERS
#define RAZ_SWAPCHAIN_HEADERS
#include "structs.h"
#include "vk_tools.h"
#include "debug.h"
#include  "render_pipeline.h"
void createSwapChain(struct RazWindow* window, struct RazSwapChain* swapChain);
void createImageViews(struct RazWindow* window, struct RazSwapChain* swapChain);

VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
VkExtent2D chooseSwapExtent(GLFWwindow *window,const VkSurfaceCapabilitiesKHR& capabilities);
void recreateSwapChain(struct Engine_App* state);
void cleanupSwapChain(RazSwapChain *swapChain,VkDevice device );

#endif // !SWAPCHAIN_
