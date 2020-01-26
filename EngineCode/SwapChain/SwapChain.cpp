#include <SwapChain/SwapChain.h>
#include <SwapChain/SwapChainSupportDetails.h>
#include <Queues/QueueFamilyIndices.h>
#include <stdexcept>
void SwapChain::CreateSwapChain(const CreateSwapChainParams& Params)
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

    if (vkCreateSwapchainKHR(Params.m_LogicalDevice.GetLogicalDevice(), &createInfo, nullptr, &swapChain) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create swap chain!");
    }

    vkGetSwapchainImagesKHR(Params.m_LogicalDevice.GetLogicalDevice(), swapChain, &imageCount, nullptr);
    swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(Params.m_LogicalDevice.GetLogicalDevice(), swapChain, &imageCount, swapChainImages.data());

    swapChainImageFormat = surfaceFormat.format;
    swapChainExtent = extent;
}

void SwapChain::Release(const VkDevice& device)
{
    vkDestroySwapchainKHR(device, swapChain, nullptr);
}

const std::vector<VkImage>& SwapChain::GetSwapChainImages() const
{
    return swapChainImages;
}

const VkFormat& SwapChain::GetSwapChainImageFormat() const
{
    return swapChainImageFormat;
}

const VkExtent2D& SwapChain::GetSwapChainExtent() const
{
    return swapChainExtent;
}
