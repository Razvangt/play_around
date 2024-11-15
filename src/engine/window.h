#pragma once
#include "vk_tools.h"


static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto app                = reinterpret_cast<struct Engine_App*>(glfwGetWindowUserPointer(window));
    app->framebufferResized = true;
}


// Glfw init window
void initWindow(struct Engine_App *state);
void createInstance(struct RazWindow *window);
void createSurface(struct RazWindow *window);
void pickPhysicalDevice(struct Engine_App *state);
bool isDeviceSuitable(VkSurfaceKHR surface,VkPhysicalDevice device);
void createLogicalDevice(struct Engine_App *state);

