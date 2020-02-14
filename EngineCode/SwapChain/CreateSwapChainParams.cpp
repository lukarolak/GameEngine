#include "CreateSwapChainParams.h"
CreateSwapChainParams::CreateSwapChainParams(const CPhysicalDevice& PhysicalDevice, const QueueFamilyIndices& QueueFamilyIndices, const VkSurfaceKHR& Surface, GLFWwindow* Window, const CValidation& ValidationLayers)
	: m_PhysicalDevice(PhysicalDevice)
	, m_QueueFamilyIndices(QueueFamilyIndices)
	, m_Surface(Surface)
	, m_Window(Window)
	, m_ValidationLayers(ValidationLayers)
{
}
