#pragma once
#include <Buffers/Buffer.h>
class CStagingBuffer : public CBuffer 
{
public:
	template <typename DataType>
	void CreateStagingBuffer(const std::vector<DataType>& Data, const VkDevice& LogicalDevice, const CPhysicalDevice& PhysicalDevice)
	{
		VkDeviceSize BufferSize = sizeof(Data[0]) * Data.size();
		CCreateBufferParams Params(LogicalDevice, PhysicalDevice, BufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		CreateBuffer(Params);
		CopyDataToBuffer(LogicalDevice, Data.data());
	}

	void Release(const VkDevice& Device);
private:

};