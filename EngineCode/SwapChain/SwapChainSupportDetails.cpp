#include <SwapChain/SwapChainSupportDetails.h>
#include <Debuging/Assert.h>
#include <Window/Resolution.h>
#include <algorithm>
void SwapChainSupportDetails::InitSwapChainSupportDetails(const VkPhysicalDevice Device, const VkSurfaceKHR& Surface)
{
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(Device, Surface, &m_Capabilities);

	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(Device, Surface, &formatCount, nullptr);

	if (formatCount != 0) 
	{
		m_Formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(Device, Surface, &formatCount, m_Formats.data());
	}

	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(Device, Surface, &presentModeCount, nullptr);

	if (presentModeCount != 0) 
	{
		m_PresentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(Device, Surface, &presentModeCount, m_PresentModes.data());
	}

	SwapChainSupportDetailsInited = true;
}

bool SwapChainSupportDetails::IsSwapChainAdequate()
{
	ENG_ASSERT(SwapChainSupportDetailsInited, "SwapChainSupportDetails has not been inited");

	return m_Formats.empty() == false && m_PresentModes.empty() == false;
}

VkSurfaceFormatKHR SwapChainSupportDetails::GetOptimalSwapSurfaceFormat()
{
	for (const auto& availableFormat : m_Formats) 
	{
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) 
		{
			return availableFormat;
		}
	}

	return m_Formats[0];
}

VkPresentModeKHR SwapChainSupportDetails::GetOptimalSwapPresentMode()
{
	for (const auto& availablePresentMode : m_PresentModes) 
	{
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) 
		{
			return availablePresentMode;
		}
	}

	return VK_PRESENT_MODE_FIFO_KHR;
}

VkExtent2D SwapChainSupportDetails::GetOptimalSwapChainExtent(GLFWwindow* Window, const WindowResolution& Resolution)
{
	if (m_Capabilities.currentExtent.width != UINT32_MAX) 
	{
		return m_Capabilities.currentExtent;
	}
	else 
	{
		int width;
		int height;
		glfwGetFramebufferSize(Window, &width, &height);

		VkExtent2D actualExtent = { static_cast<engIntU32>(width), static_cast<engIntU32>(height) };
		
		actualExtent.width = std::max(m_Capabilities.minImageExtent.width, std::min(m_Capabilities.maxImageExtent.width, actualExtent.width));
		actualExtent.height = std::max(m_Capabilities.minImageExtent.height, std::min(m_Capabilities.maxImageExtent.height, actualExtent.height));
		
		return actualExtent;
	}
}

const VkSurfaceCapabilitiesKHR& SwapChainSupportDetails::GetCapabilities()
{
	return m_Capabilities;
}
