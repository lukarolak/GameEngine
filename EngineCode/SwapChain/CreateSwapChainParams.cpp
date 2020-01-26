#include "CreateSwapChainParams.h"

CreateSwapChainParams::CreateSwapChainParams(const PhysicalDevice& PhysicalDevice, const VkSurfaceKHR& Surface, const WindowResolution& Resolution, const LogicalDevice& LogicalDevice)
	: m_PhysicalDevice(PhysicalDevice)
	, m_Surface(Surface)
	, m_Resolution(Resolution)
	, m_LogicalDevice(LogicalDevice)
{
}
