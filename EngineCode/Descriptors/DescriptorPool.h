#pragma once
#include <vulkan/vulkan_core.h>
#include <TypeDefs/TypeDefs.h>
class DescriptorPool
{
public:
	void CreateDescriptorPool(const VkDevice& Device, const engIntU32 descriprtorAmount);
	void Release(const VkDevice& Device);
private:
	VkDescriptorPool m_DescriptorPool;
};