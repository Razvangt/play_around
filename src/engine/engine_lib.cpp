#include "engine_lib.h"

void run(struct Engine_App* state) {
    initWindow(state);
    initVulkan(state);
    mainLoop(state);
    cleanup(state);
}

void initVulkan(struct Engine_App* state) {

    // window.h
    createInstance(&state->window);
    setupDebugMessenger(state->window.instance, &state->debugMessenger);
    createSurface(&state->window);
    pickPhysicalDevice(&state->window);
    createLogicalDevice(state);

    // swapchain.h
    createSwapChain(&state->window, &state->swapChain);
    createImageViews(&state->window, &state->swapChain);

    // render_pipeline.h
    createRenderPass(state);
    createDescriptorSetLayout(state);
    createGraphicsPipeline(state);

    // vk_commands.h
    createCommandPool(state);
    createDepthResources(state);
    createFramebuffers(&state->swapChain, state->window.device, state->renderPass,state ->depthImageView);
    createTextureImage(state);
    createTextureImageView(state);
    createTextureSampler(state);
    createVertexBuffer(state);  // render_pipeline.h
    createIndexBuffer(state);   // render_pipeline.h
    createUniformBuffer(state); // render_pipeline.h
    createDescriptorPool(state);
    createDescriptorSets(state);
    createCommandBuffers(state);
    createSyncObjects(state);
}

void mainLoop(struct Engine_App* state) {
    while (!glfwWindowShouldClose(state->window.handle)) {
        glfwPollEvents();
        drawFrame(state);
    }

    vkDeviceWaitIdle(state->window.device);
}


void cleanup(struct Engine_App* state) {
    cleanupSwapChain(&state->swapChain, state->window.device);

    vkDestroyImageView(state -> window.device,state-> depthImageView, nullptr);
    vkDestroyImage(state -> window.device,state-> depthImage, nullptr);
    vkFreeMemory(state -> window.device, state -> depthImageMemory, nullptr);
    
    vkDestroySampler(state -> window.device, state->textureSampler, nullptr);
    vkDestroyImageView(state -> window.device, state->textureImageView, nullptr);
    vkDestroyImage(state -> window.device, state -> textureImage, nullptr);
    vkFreeMemory(state -> window.device, state -> textureImageMemory, nullptr);
    
    vkDestroyImage(state ->window.device, state->textureImage, nullptr);
    vkFreeMemory(state -> window.device, state-> textureImageMemory, nullptr);
 
    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroyBuffer(state ->window.device, state -> uniformBuffers[i], nullptr);
        vkFreeMemory(state -> window.device, state -> uniformBuffersMemory[i], nullptr);
    }
    
    vkDestroyDescriptorPool(state->window.device, state->descriptorPool, nullptr);
    vkDestroyDescriptorSetLayout(state->window.device, state->descriptorSetLayout, nullptr);
 
    vkDestroyBuffer(state->window.device, state->indexBuffer, nullptr);
    vkFreeMemory(state->window.device, state->indexBufferMemory, nullptr);

    vkDestroyBuffer(state->window.device, state->vertexBuffer, nullptr);
    vkFreeMemory(state->window.device, state->vertexBufferMemory, nullptr);

    // Vertex Buffer
    vkDestroyBuffer(state->window.device, state->vertexBuffer, nullptr);
    vkFreeMemory(state->window.device, state->vertexBufferMemory, nullptr);

    vkDestroyPipeline(state->window.device, state->graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(state->window.device, state->pipelineLayout, nullptr);

    vkDestroyRenderPass(state->window.device, state->renderPass, nullptr);

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(state->window.device, state->renderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(state->window.device, state->imageAvailableSemaphores[i], nullptr);
        vkDestroyFence(state->window.device, state->inFlightFences[i], nullptr);
    }

    vkDestroyCommandPool(state->window.device, state->commandPool, nullptr);

    vkDestroyDevice(state->window.device, nullptr);

    if (enableValidationLayers) {
        DestroyDebugUtilsMessengerEXT(state->window.instance, state->debugMessenger, nullptr);
    }

    vkDestroySurfaceKHR(state->window.instance, state->window.surface, nullptr);
    vkDestroyInstance(state->window.instance, nullptr);

    glfwDestroyWindow(state->window.handle);

    glfwTerminate();
}


void drawFrame(struct Engine_App* state) {
    vkWaitForFences(state->window.device, 1, &state->inFlightFences[state->currentFrame], VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(state->window.device, state->swapChain.handle, UINT64_MAX,
    state->imageAvailableSemaphores[state->currentFrame], VK_NULL_HANDLE, &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        recreateSwapChain(state);
        return;
    } else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
        throw std::runtime_error("failed to adcquire swap chain image!");
    }

    vkResetFences(state->window.device, 1, &state->inFlightFences[state->currentFrame]);

    vkResetCommandBuffer(state->commandBuffers[state->currentFrame],
    /*VkCommandBufferResetFlagBits*/ 0);
    recordCommandBuffer(state, state->commandBuffers[state->currentFrame], imageIndex);
    

    updateUniformBuffer(state,state -> currentFrame);

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[]      = { state->imageAvailableSemaphores[state->currentFrame] };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount     = 1;
    submitInfo.pWaitSemaphores        = waitSemaphores;
    submitInfo.pWaitDstStageMask      = waitStages;

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers    = &state->commandBuffers[state->currentFrame];

    VkSemaphore signalSemaphores[]  = { state->renderFinishedSemaphores[state->currentFrame] };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores    = signalSemaphores;

    if (vkQueueSubmit(state->graphicsQueue, 1, &submitInfo, state->inFlightFences[state->currentFrame]) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores    = signalSemaphores;

    VkSwapchainKHR swapChains[] = { state->swapChain.handle };
    presentInfo.swapchainCount  = 1;
    presentInfo.pSwapchains     = swapChains;

    presentInfo.pImageIndices = &imageIndex;

    result = vkQueuePresentKHR(state->presentQueue, &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || state->framebufferResized) {
        state->framebufferResized = false;
        recreateSwapChain(state);
    } else if (result != VK_SUCCESS) {
        throw std::runtime_error("failed to present swap chain image!");
    }

    state->currentFrame = (state->currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}
