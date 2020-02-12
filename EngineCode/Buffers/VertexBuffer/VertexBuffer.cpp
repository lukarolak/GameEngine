#include "VertexBuffer.h"
#include <Buffers/StagingBuffer/StagingBuffer.h>

void CVertexBuffer::CreateVertexBuffer(const CCreateVertexBufferParams& Params)
{
	VkDeviceSize bufferSize = sizeof(Params.m_Data[0]) * Params.m_Data.size();
	
	CStagingBuffer stagingBuffer;
	stagingBuffer.CreateStagingBuffer(Params.m_Data, Params.m_LogicalDevice, Params.m_PhysicalDevice);

	CCreateBufferParams createBufferParams(Params.m_LogicalDevice, Params.m_PhysicalDevice, bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	CreateBuffer(createBufferParams);

	CopyBufferToBufferParams copyBufferToBufferParams();
	CopyBufferToBuffer(stagingBuffer, Params.m_CopyBufferToBufferParams);

	stagingBuffer.Release(Params.m_LogicalDevice);
}

void CVertexBuffer::Release(const VkDevice& Device)
{
	CBuffer::Release(Device);
}
