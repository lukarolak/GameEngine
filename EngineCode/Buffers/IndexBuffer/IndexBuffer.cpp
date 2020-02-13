#include <Buffers/IndexBuffer/IndexBuffer.h>

void CIndexBuffer::Release(const VkDevice& Device)
{
	CBuffer::Release(Device);
}

void CIndexBuffer::DrawBuffer(const VkCommandBuffer& CommandBuffer)
{
	vkCmdDrawIndexed(CommandBuffer, m_BufferSize, 1, 0, 0, 0);
}

void CIndexBuffer::BindBuffer(const VkCommandBuffer& CommandBuffer)
{
	vkCmdBindIndexBuffer(CommandBuffer, CBuffer::GetBuffer(), 0, m_IndexType);
}
