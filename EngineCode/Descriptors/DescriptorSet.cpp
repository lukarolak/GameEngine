#include <Descriptors/DescriptorSet.h>
#include <Debuging/Assert.h>

//napravi jedan descriptor set
void DescriptorSet::CreateDescriptorSet(engIntU32 DescriptorSetAmount, const VkDescriptorSetLayout& DescriptorSetLayout, const VkDescriptorPool& DescriptorPool, const VkDevice& Device)
{
	std::vector<VkDescriptorSetLayout> layouts(DescriptorSetAmount, DescriptorSetLayout);
	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = DescriptorPool;
	allocInfo.descriptorSetCount = DescriptorSetAmount;
	allocInfo.pSetLayouts = layouts.data();

	m_DescriptorSets.resize(DescriptorSetAmount);

	VkResult result;
	result = vkAllocateDescriptorSets(Device, &allocInfo, m_DescriptorSets.data());
	ENG_ASSERT(result == VK_SUCCESS, "failed to allocate descriptor sets!");
}
