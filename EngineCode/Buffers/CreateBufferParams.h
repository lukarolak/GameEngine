#pragma once
#include <vulkan/vulkan_core.h>
#include <Devices/PhysicalDevice.h>
class CCreateBufferParams
{
public:
	CCreateBufferParams(
		const VkDevice& LogicalDevice, 
		const CPhysicalDevice& PhysicalDevice, 
		const engIntU32& Size,
		const VkBufferUsageFlags& Usage,
		const VkMemoryPropertyFlags& Properties);

public:
	const VkDevice& m_LogicalDevice;
	const CPhysicalDevice& m_PhysicalDevice;
	const engIntU32& m_Size;
	const VkBufferUsageFlags& m_Usage;
	const VkMemoryPropertyFlags& m_Properties;
};