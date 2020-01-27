#pragma once
#include <vulkan/vulkan_core.h>
#include <Devices/PhysicalDevice.h>
#include <Devices/LogicalDevice.h>
class CCommandPool
{
public:
	void CreateCommandPool(const CPhysicalDevice& PhysicalDevice, const CLogicalDevice& LogicalDevice);
	void Release(const CLogicalDevice& LogicalDevice);
	const VkCommandPool& GetCommandPool() const;
private:
	VkCommandPool commandPool;
};