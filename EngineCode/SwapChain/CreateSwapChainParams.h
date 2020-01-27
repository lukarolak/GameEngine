#pragma once
#include <Devices/LogicalDevice.h>
#include <Devices/PhysicalDevice.h>
#include <Window/Resolution.h>
class CreateSwapChainParams
{
public:
	CreateSwapChainParams(
	const CPhysicalDevice& PhysicalDevice,
	const VkSurfaceKHR& Surface,
	const WindowResolution& Resolution,
	const CLogicalDevice& LogicalDevice
	);

public:
	const CPhysicalDevice& m_PhysicalDevice;
	const VkSurfaceKHR& m_Surface;
	const WindowResolution& m_Resolution;
	const CLogicalDevice& m_LogicalDevice;
};