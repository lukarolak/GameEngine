#include "StagingBuffer.h"

void CStagingBuffer::CreateStagingBuffer(std::vector<CVertex>& Data, const VkDevice& LogicalDevice, const CPhysicalDevice& PhysicalDevice)
{
	VkDeviceSize BufferSize = sizeof(Data[0]) * Data.size();
	CCreateBufferParams Params(LogicalDevice, PhysicalDevice, BufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
	CreateBuffer(Params);
	CopyDataToBuffer(LogicalDevice, Data.data());	
}

void CStagingBuffer::Release(const VkDevice& Device)
{
	CBuffer::Release(Device);
}
