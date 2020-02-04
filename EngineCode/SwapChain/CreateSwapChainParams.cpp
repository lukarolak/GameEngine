#include "CreateSwapChainParams.h"
CreateSwapChainParams::CreateSwapChainParams(const VkPhysicalDevice& PhysicalDevice, const QueueFamilyIndices& QueueFamilyIndices, const VkSurfaceKHR& Surface, const WindowResolution& Resolution, const VkDevice& LogicalDevice, GLFWwindow* Window)
	: m_PhysicalDevice(PhysicalDevice)
	, m_QueueFamilyIndices(QueueFamilyIndices)
	, m_Surface(Surface)
	, m_Resolution(Resolution)
	, m_LogicalDevice(LogicalDevice)
	, m_Window(Window)
{
}
