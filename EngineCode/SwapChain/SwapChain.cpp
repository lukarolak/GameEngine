#include <SwapChain/SwapChain.h>
#include <SwapChain/SwapChainSupportDetails.h>
#include <Queues/QueueFamilyIndices.h>
#include <stdexcept>
void CSwapChain::CreateSwapChain(const CreateSwapChainParams& Params)
{
    m_LogicalDevice.CreateLogicalDevice(Params.m_PhysicalDevice, Params.m_ValidationLayers);
    const VkDevice device = m_LogicalDevice.GetLogicalDevice();
    m_CommandPool.CreateCommandPool(Params.m_QueueFamilyIndices.GetGraphicsFamily().value(), device);
    CreateSwapChainDependants(Params);
}

void CSwapChain::Release()
{
    m_LogicalDevice.WaitForDeviceIdle();
    const VkDevice device = m_LogicalDevice.GetLogicalDevice();
    m_CommandPool.Release(device);
    ReleaseSwapChainDependants();
    m_LogicalDevice.Release();
}

void CSwapChain::RecreateSwapChain(const CreateSwapChainParams& Params)
{
    vkDeviceWaitIdle(m_LogicalDevice.GetLogicalDevice());
    const bool modifyCommandPool = false;
    ReleaseSwapChainDependants();
    CreateSwapChainDependants(Params);
}

void CSwapChain::DrawFrame()
{
    const VkDevice device = m_LogicalDevice.GetLogicalDevice();
    const CSynchronizationObjectsGroup& synchronizationObjectGroup = m_LogicalDevice.GetSynchronizationObjectsGroup();
    const CSynchronizationObjects& synchronizationObjectsForThisFrame = synchronizationObjectGroup.GetSynchronizationObjectGroup()[m_CurrentFrame];

    vkWaitForFences(m_LogicalDevice.GetLogicalDevice(), 1, &synchronizationObjectsForThisFrame.GetInFlightFence(), VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;

    VkResult result = vkAcquireNextImageKHR(
        m_LogicalDevice.GetLogicalDevice(),
        m_SwapChain,
        UINT64_MAX,
        synchronizationObjectsForThisFrame.GetImageAvailableSemaphore(),
        VK_NULL_HANDLE,
        &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) 
    {
        RecreateSwapChain();
        return;
    }
    else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) 
    {
        throw std::runtime_error("failed to acquire swap chain image!");
    }

    // Check if a previous frame is using this image (i.e. there is its fence to wait on)
    if (synchronizationObjectsForThisFrame.GetImageInFlightFence() != VK_NULL_HANDLE)
    {
        vkWaitForFences(device, 1, &synchronizationObjectsForThisFrame.GetImageInFlightFence(), VK_TRUE, UINT64_MAX);
    }
    // Mark the image as now being in use by this frame
    m_LogicalDevice.SetImageInUse(m_CurrentFrame);

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = { synchronizationObjectsForThisFrame.GetImageAvailableSemaphore() };
    VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &m_CommandBuffer.GetCommandBuffers()[imageIndex];

    VkSemaphore signalSemaphores[] = { synchronizationObjectsForThisFrame.GetRenderFinishedSemaphore() };
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    vkResetFences(device, 1, &synchronizationObjectsForThisFrame.GetInFlightFence());

    if (vkQueueSubmit(m_LogicalDevice.GetGraphicsQueue(), 1, &submitInfo, synchronizationObjectsForThisFrame.GetInFlightFence()) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    VkSubpassDependency dependency = {};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = { m_SwapChain };
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;
    presentInfo.pResults = nullptr; // Optional

    vkQueuePresentKHR(m_LogicalDevice.GetPresentQueue(), &presentInfo);

    m_CurrentFrame = (m_CurrentFrame + 1) % synchronizationObjectGroup.GetMaxFramesInFlight();
}

void CSwapChain::ReleaseSwapChainDependants()
{
    const VkDevice device = m_LogicalDevice.GetLogicalDevice();
    m_FrameBuffer.Release(device);
    m_GraphicsPipeline.Release(device);
    m_RenderPass.Release(device);
    m_ImageViews.Release(device);
    vkDestroySwapchainKHR(device, m_SwapChain, nullptr);
}

void CSwapChain::CreateSwapChainDependants(const CreateSwapChainParams& Params)
{
    const VkDevice device = m_LogicalDevice.GetLogicalDevice();
    SwapChainSupportDetails swapChainSupport;
    swapChainSupport.InitSwapChainSupportDetails(Params.m_PhysicalDevice.GetPhysicalDevice(), Params.m_Surface);
    VkSurfaceFormatKHR surfaceFormat = swapChainSupport.GetOptimalSwapSurfaceFormat();
    VkPresentModeKHR presentMode = swapChainSupport.GetOptimalSwapPresentMode();
    VkExtent2D extent = swapChainSupport.GetOptimalSwapChainExtent(Params.m_Window, Params.m_Resolution);

    const VkSurfaceCapabilitiesKHR& swapChainCapabilities = swapChainSupport.GetCapabilities();
    engIntU32 imageCount = swapChainCapabilities.minImageCount + 1;
    if (swapChainCapabilities.maxImageCount > 0 && imageCount > swapChainCapabilities.maxImageCount)
    {
        imageCount = swapChainCapabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = Params.m_Surface;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    const QueueFamilyIndices& indices = Params.m_QueueFamilyIndices;
    uint32_t queueFamilyIndices[] = { indices.GetGraphicsFamily().value(), indices.GetPresentFamily().value() };

    if (indices.GetGraphicsFamily() != indices.GetPresentFamily())
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0; // Optional
        createInfo.pQueueFamilyIndices = nullptr; // Optional
    }

    createInfo.preTransform = swapChainCapabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &m_SwapChain) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create swap chain!");
    }

    vkGetSwapchainImagesKHR(device, m_SwapChain, &imageCount, nullptr);
    m_SwapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(device, m_SwapChain, &imageCount, m_SwapChainImages.data());

    m_SwapChainImageFormat = surfaceFormat.format;
    m_SwapChainExtent = extent;


    CreateImageViewsParams createImageViewParams(m_SwapChainImages, m_SwapChainImageFormat, device);
    m_ImageViews.CreateImageViews(createImageViewParams);

    m_RenderPass.CreateRenderPass(m_SwapChainImageFormat, device);

    CreateGraphicsPipelineParams createGraphicsPipelineParams(device, m_SwapChainExtent, m_RenderPass.GetRenderPass());
    m_GraphicsPipeline.CreateGraphicsPipeline(createGraphicsPipelineParams);

    CCreateFrameBuffersParams createFrameBuffersParams(m_ImageViews.GetSwapChainImageViews(), m_RenderPass.GetRenderPass(), m_SwapChainExtent, device);
    m_FrameBuffer.CreateFrameBuffers(createFrameBuffersParams);

    CCreateCommandBufferParams createCommandBufferParams(m_CommandPool.GetCommandPool(), device, m_RenderPass.GetRenderPass(), m_FrameBuffer.GetSwapChainFrameBuffers(), m_SwapChainExtent, m_GraphicsPipeline.GetGraphicsPipeline());
    m_CommandBuffer.CreateCommandBuffers(createCommandBufferParams);
}
