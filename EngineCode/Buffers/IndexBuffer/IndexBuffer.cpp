#include <Buffers/IndexBuffer/IndexBuffer.h>
#include <Debuging/Assert.h>
void CIndexBuffer::Release(const VkDevice& Device)
{
	CBuffer::Release(Device);
}

void CIndexBuffer::DrawBuffer(const VkCommandBuffer& CommandBuffer)
{
	engIntU32 indexAmount = 0;
	switch (m_IndexType)
	{
	case VK_INDEX_TYPE_UINT16:
		indexAmount = m_BufferSize / sizeof(engIntU16);
		break;
	case VK_INDEX_TYPE_UINT32:
		indexAmount = m_BufferSize / sizeof(engIntU32);
		break;
	default:
		ENG_ASSERT(false, "index type not implemented");
		break;
	}

	vkCmdDrawIndexed(CommandBuffer, indexAmount, 1, 0, 0, 0);
}

void CIndexBuffer::BindBuffer(const VkCommandBuffer& CommandBuffer)
{
	vkCmdBindIndexBuffer(CommandBuffer, CBuffer::GetBuffer(), 0, m_IndexType);
}
