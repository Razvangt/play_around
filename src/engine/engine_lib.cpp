#include "engine_lib.h"

void run(struct Engine_App* state) {
    initWindow(state);
    initVulkan(state);
    mainLoop(state);
    cleanup(state);
}




void initVulkan(struct Engine_App* state) {

  //window.h
    createInstance(&state->window);
    setupDebugMessenger(state->window.instance, &state->debugMessenger);
    createSurface(&state->window);
    pickPhysicalDevice(&state->window);
    createLogicalDevice(state);

  //swapchain.h
    createSwapChain(&state -> window, &state -> swapChain);
    createImageViews(&state -> window, &state -> swapChain);
   
  //render_pipeline.h
    createRenderPass(state);
    createGraphicsPipeline(state);

  //swapchain.h
    createFramebuffers(&state -> swapChain, state ->window.device, state -> renderPass);
    
    createCommandPool(state);
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







void createCommandPool(struct Engine_App* state) {
    QueueFamilyIndices queueFamilyIndices = findQueueFamilies(state->window.surface, state->window.physicalDevice);

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags            = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

    if (vkCreateCommandPool(state->window.device, &poolInfo, nullptr, &state->commandPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create command pool!");
    }
}

void createCommandBuffers(struct Engine_App* state) {
    state->commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool        = state->commandPool;
    allocInfo.level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = (uint32_t)state->commandBuffers.size();

    if (vkAllocateCommandBuffers(state->window.device, &allocInfo, state->commandBuffers.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}

void recordCommandBuffer(struct Engine_App* state, VkCommandBuffer commandBuffer, uint32_t imageIndex) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

        if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
            throw std::runtime_error("failed to begin recording command buffer!");
        }

        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType             = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass        = state -> renderPass;
        renderPassInfo.framebuffer       = state -> swapChain.Framebuffers[imageIndex];
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = state -> swapChain.Extent;

        VkClearValue clearColor        = { { { 0.0f, 0.0f, 0.0f, 1.0f } } };
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues    = &clearColor;

        vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, state -> graphicsPipeline);

        VkViewport viewport{};
        viewport.x        = 0.0f;
        viewport.y        = 0.0f;
        viewport.width    = (float)state -> swapChain.Extent.width;
        viewport.height   = (float)state -> swapChain.Extent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;
        vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

        VkRect2D scissor{};
        scissor.offset = { 0, 0 };
        scissor.extent = state ->swapChain.Extent;
        vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

        vkCmdDraw(commandBuffer, 3, 1, 0, 0);

        vkCmdEndRenderPass(commandBuffer);

        if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to record command buffer!");
        }}

void createSyncObjects(struct Engine_App* state) {
    state->imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    state->renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    state->inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        if (vkCreateSemaphore(state->window.device, &semaphoreInfo, nullptr, &state->imageAvailableSemaphores[i]) != VK_SUCCESS ||
        vkCreateSemaphore(state->window.device, &semaphoreInfo, nullptr, &state->renderFinishedSemaphores[i]) != VK_SUCCESS ||
        vkCreateFence(state->window.device, &fenceInfo, nullptr, &state->inFlightFences[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create synchronization objects for a frame!");
        }
    }
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

