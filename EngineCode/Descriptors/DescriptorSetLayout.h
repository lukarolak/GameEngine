#pragma once
#include <vulkan/vulkan_core.h>
class CDescriptorSetLayout
{
public:
	void CreateDescriptorSetLayout(const VkDevice& Device);
	const VkDescriptorSetLayout& GetDescriptorSetLayout();
	void Release(const VkDevice& Device);
private:
	VkDescriptorSetLayout m_DescriptorSetLayout;
};