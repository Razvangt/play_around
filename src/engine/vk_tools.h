#ifndef RAZ_VK_TOOLS_HEADERS
#define RAZ_VK_TOOLS_HEADERS
#include "structs.h"
bool checkValidationLayerSupport();
QueueFamilyIndices findQueueFamilies(VkSurfaceKHR surface,VkPhysicalDevice device);
bool checkDeviceExtensionSupport(VkPhysicalDevice device);
SwapChainSupportDetails querySwapChainSupport(VkSurfaceKHR surface,VkPhysicalDevice device);
std::vector<const char*> getRequiredExtensions();
static std::vector<char> readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();

    return buffer;
}


#endif // !RAZ_VK_TOOLS_HEADERS
