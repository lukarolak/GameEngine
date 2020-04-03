#pragma once
#include <vulkan/vulkan_core.h>
#include <TypeDefs/TypeDefs.h>
#include <vector>
class DescriptorSet
{
public:
	void CreateDescriptorSet(engIntU32 DescriptorSetAmount, const VkDescriptorSetLayout& DescriptorSetLayout, const VkDescriptorPool& DescriptorPool, const VkDevice& Device);
private:
	std::vector<VkDescriptorSet> m_DescriptorSets;
};