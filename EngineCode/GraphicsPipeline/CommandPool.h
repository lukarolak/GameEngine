#pragma once
#include <vulkan/vulkan_core.h>
#include <Devices/PhysicalDevice.h>
#include <Devices/LogicalDevice.h>
class CCommandPool
{
public:
	void CreateCommandPool(const engIntU32& GraphicsFamily, const VkDevice& LogicalDevice);
	void Release(const VkDevice& Device);
	const VkCommandPool& GetCommandPool() const;
private:
	VkCommandPool commandPool;
};