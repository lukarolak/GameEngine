#pragma once
#include <Devices/LogicalDevice.h>
#include <Devices/PhysicalDevice.h>
#include <Window/Resolution.h>
class CreateSwapChainParams
{
public:
	CreateSwapChainParams(
	const PhysicalDevice& PhysicalDevice,
	const VkSurfaceKHR& Surface,
	const WindowResolution& Resolution,
	const LogicalDevice& LogicalDevice
	);

public:
	const PhysicalDevice& m_PhysicalDevice;
	const VkSurfaceKHR& m_Surface;
	const WindowResolution& m_Resolution;
	const LogicalDevice& m_LogicalDevice;
};