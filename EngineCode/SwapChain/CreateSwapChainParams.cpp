#include "CreateSwapChainParams.h"

CreateSwapChainParams::CreateSwapChainParams(const CPhysicalDevice& PhysicalDevice, const VkSurfaceKHR& Surface, const WindowResolution& Resolution, const CLogicalDevice& LogicalDevice)
	: m_PhysicalDevice(PhysicalDevice)
	, m_Surface(Surface)
	, m_Resolution(Resolution)
	, m_LogicalDevice(LogicalDevice)
{
}
