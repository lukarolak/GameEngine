#pragma once
#include <Devices/LogicalDevice.h>
#include <Devices/PhysicalDevice.h>
#include <Window/Resolution.h>
#include <GLFW/glfw3.h>
class CreateSwapChainParams
{
public:
	CreateSwapChainParams(
	const VkPhysicalDevice& PhysicalDevice,
	const QueueFamilyIndices& QueueFamilyIndices,
	const VkSurfaceKHR& Surface,
	const WindowResolution& Resolution,
	const VkDevice& LogicalDevice,
	GLFWwindow* m_Window
	);

public:
	const VkPhysicalDevice& m_PhysicalDevice;
	const QueueFamilyIndices& m_QueueFamilyIndices;
	const VkSurfaceKHR& m_Surface;
	const WindowResolution& m_Resolution;
	const VkDevice& m_LogicalDevice;
	GLFWwindow* m_Window;
};