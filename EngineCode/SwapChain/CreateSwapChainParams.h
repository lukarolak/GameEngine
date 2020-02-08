#pragma once
#include <Devices/LogicalDevice.h>
#include <Devices/PhysicalDevice.h>
#include <Window/Resolution.h>
#include <GLFW/glfw3.h>
class CreateSwapChainParams
{
public:
	CreateSwapChainParams(
	const CPhysicalDevice& PhysicalDevice,
	const QueueFamilyIndices& QueueFamilyIndices,
	const VkSurfaceKHR& Surface,
	const WindowResolution& Resolution,
	GLFWwindow* m_Window,
	const CValidation& ValidationLayers
	);

public:
	const CPhysicalDevice& m_PhysicalDevice;
	const QueueFamilyIndices& m_QueueFamilyIndices;
	const VkSurfaceKHR& m_Surface;
	const WindowResolution& m_Resolution;
	GLFWwindow* m_Window;
	const CValidation& m_ValidationLayers;
};