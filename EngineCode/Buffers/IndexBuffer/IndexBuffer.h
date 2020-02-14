#pragma once
#include <Buffers/Buffer.h>
#include <Buffers/IndexBuffer/CreateIndexBufferParams.h>
#include <Buffers/StagingBuffer/StagingBuffer.h>
class CIndexBuffer : public CBuffer
{
public:
    template <typename DataType>
	void CreateIndexBuffer(const CCreateIndexBufferParams<DataType>& Params);
    void Release(const VkDevice& Device);
    void DrawBuffer(const VkCommandBuffer& CommandBuffer) override;
    void BindBuffer(const VkCommandBuffer& CommandBuffer) override;
private:
    engIntU32 m_BufferSize;
    VkIndexType m_IndexType;
};

template<typename DataType>
inline void CIndexBuffer::CreateIndexBuffer(const CCreateIndexBufferParams<DataType>& Params)
{
    const bool usingUINT32 = sizeof(DataType) > sizeof(engIntU16);
    if (usingUINT32)
    {
        m_IndexType = VkIndexType::VK_INDEX_TYPE_UINT32;
    }
    else
    {
        m_IndexType = VkIndexType::VK_INDEX_TYPE_UINT16;
    }

    const VkDevice& device = Params.m_LogicalDevice.GetLogicalDevice();

    m_BufferSize = static_cast<engIntU32>(sizeof(Params.m_Data[0]) * Params.m_Data.size());

    CStagingBuffer stagingBuffer;
    stagingBuffer.CreateStagingBuffer(Params.m_Data, device, Params.m_PhysicalDevice);

    CCreateBufferParams createBufferParams(device, Params.m_PhysicalDevice, m_BufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
    CreateBuffer(createBufferParams);

    CopyBufferToBufferParams copyBufferToBufferParams(m_BufferSize, Params.m_CommandPool, Params.m_LogicalDevice);
    CopyBufferToBuffer(stagingBuffer, copyBufferToBufferParams);

    stagingBuffer.Release(device);
}
