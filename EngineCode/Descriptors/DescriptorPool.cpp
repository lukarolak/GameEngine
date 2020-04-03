#include <Descriptors/DescriptorPool.h>
#include <Debuging/Assert.h>
void DescriptorPool::CreateDescriptorPool(const VkDevice& Device, const engIntU32 descriprtorAmount)
{
	VkDescriptorPoolSize poolSize = {};
	poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSize.descriptorCount = descriprtorAmount;

	VkDescriptorPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = 1;
	poolInfo.pPoolSizes = &poolSize;

	poolInfo.maxSets = descriprtorAmount;

	VkResult result;
	result = vkCreateDescriptorPool(Device, &poolInfo, nullptr, &m_DescriptorPool);
	ENG_ASSERT(result == VK_SUCCESS, "failed to create descriptor pool!");
}

void DescriptorPool::Release(const VkDevice& Device)
{
	vkDestroyDescriptorPool(Device, m_DescriptorPool, nullptr);
}
