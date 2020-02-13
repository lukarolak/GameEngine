#pragma once
#include <vector>
#include <Vertex/Vertex.h>
#include <Devices/PhysicalDevice.h>
#include <Buffers/CreateBufferParams.h>
#include <Buffers/CopyBufferToBufferParams.h>
class CBuffer
{
public:
	virtual ~CBuffer();
	VkBuffer& GetBuffer();
	virtual void BindBuffer(const VkCommandBuffer& CommandBuffer);
	virtual void DrawBuffer(const VkCommandBuffer& CommandBuffer);
protected:
	void CreateBuffer(const CCreateBufferParams& Params);
	void CopyDataToBuffer(const VkDevice& Device, const void* data);
	void CopyBufferToBuffer(CBuffer& SourceBuffer, const CopyBufferToBufferParams& Params);
	void Release(const VkDevice& Device);
private:
	engIntU32 BufferSize;
	VkBuffer m_Buffer;
	VkDeviceMemory m_BufferMemory;
	bool m_BufferReleased = false;
};