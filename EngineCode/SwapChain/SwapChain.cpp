#include <SwapChain/SwapChain.h>
#include <SwapChain/SwapChainSupportDetails.h>
#include <Queues/QueueFamilyIndices.h>
#include <stdexcept>
void CSwapChain::CreateSwapChain(const CreateSwapChainParams& Params)
{
    SwapChainSupportDetails swapChainSupport;
    swapChainSupport.InitSwapChainSupportDetails(Params.m_PhysicalDevice.GetPhysicalDevice(), Params.m_Surface);
    VkSurfaceFormatKHR surfaceFormat = swapChainSupport.GetOptimalSwapSurfaceFormat();
    VkPresentModeKHR presentMode = swapChainSupport.GetOptimalSwapPresentMode();
    VkExtent2D extent = swapChainSupport.GetOptimalSwapExtent(Params.m_Resolution);
    
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

    const QueueFamilyIndices& indices = Params.m_PhysicalDevice.GetQueueFamilyIndices();
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

    if (vkCreateSwapchainKHR(Params.m_LogicalDevice.GetLogicalDevice(), &createInfo, nullptr, &m_SwapChain) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create swap chain!");
    }

    vkGetSwapchainImagesKHR(Params.m_LogicalDevice.GetLogicalDevice(), m_SwapChain, &imageCount, nullptr);
    m_SwapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(Params.m_LogicalDevice.GetLogicalDevice(), m_SwapChain, &imageCount, m_SwapChainImages.data());

    m_SwapChainImageFormat = surfaceFormat.format;
    m_SwapChainExtent = extent;


    CreateImageViewsParams createImageViewParams(m_SwapChainImages, m_SwapChainImageFormat, Params.m_LogicalDevice.GetLogicalDevice());
    m_ImageViews.CreateImageViews(createImageViewParams);

    m_RenderPass.CreateRenderPass(m_SwapChainImageFormat, Params.m_LogicalDevice.GetLogicalDevice());

    CreateGraphicsPipelineParams createGraphicsPipelineParams(Params.m_LogicalDevice.GetLogicalDevice(), m_SwapChainExtent, m_RenderPass.GetRenderPass());
    m_GraphicsPipeline.CreateGraphicsPipeline(createGraphicsPipelineParams);

    CCreateFrameBuffersParams createFrameBuffersParams(m_ImageViews.GetSwapChainImageViews(), m_RenderPass.GetRenderPass(), m_SwapChainExtent, Params.m_LogicalDevice.GetLogicalDevice());
    m_FrameBuffer.CreateFrameBuffers(createFrameBuffersParams);
}

void CSwapChain::Release(const VkDevice& device)
{
    m_FrameBuffer.Release(device);
    m_GraphicsPipeline.Release(device);
    m_RenderPass.Release(device);
    m_ImageViews.Release(device);
    vkDestroySwapchainKHR(device, m_SwapChain, nullptr);
}

const std::vector<VkImage>& CSwapChain::GetSwapChainImages() const
{
    return m_SwapChainImages;
}

const VkFormat& CSwapChain::GetSwapChainImageFormat() const
{
    return m_SwapChainImageFormat;
}

const VkExtent2D& CSwapChain::GetSwapChainExtent() const
{
    return m_SwapChainExtent;
}

const VkSwapchainKHR& CSwapChain::GetSwapChain() const
{
    return m_SwapChain;
}

const CImageViews& CSwapChain::GetImageViews() const
{
    return m_ImageViews;
}

const CRenderPass& CSwapChain::GetRenderPass() const
{
    return m_RenderPass;
}

const CGraphicsPipeline& CSwapChain::GetGraphicsPipeline() const
{
    return m_GraphicsPipeline;
}

const CFrameBuffer& CSwapChain::GetFrameBuffer() const
{
    return m_FrameBuffer;
}
