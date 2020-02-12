#pragma once
#include <vulkan/vulkan_core.h>
#include <Devices/LogicalDevice.h>
class CopyBufferToBufferParams
{
public:
	CopyBufferToBufferParams(const VkDeviceSize& Size, const VkCommandPool& CommandPool, const CLogicalDevice& LogicalDevice);
public:
	const VkDeviceSize& m_Size;
	const VkCommandPool& m_CommandPool;
	const CLogicalDevice& m_LogicalDevice;
};