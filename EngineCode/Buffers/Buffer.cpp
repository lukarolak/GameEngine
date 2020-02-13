#include <Buffers/Buffer.h>
#include <Debuging/Assert.h>
void CBuffer::CreateBuffer(const CCreateBufferParams& Params)
{
	BufferSize = static_cast<engIntU32>(Params.m_Size);

	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = Params.m_Size;
	bufferInfo.usage = Params.m_Usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(Params.m_LogicalDevice, &bufferInfo, nullptr, &m_Buffer) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create buffer!");
	}

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(Params.m_LogicalDevice, m_Buffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = Params.m_PhysicalDevice.GetMemoryType(memRequirements.memoryTypeBits, Params.m_Properties);

	if (vkAllocateMemory(Params.m_LogicalDevice, &allocInfo, nullptr, &m_BufferMemory) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to allocate buffer memory!");
	}

	vkBindBufferMemory(Params.m_LogicalDevice, m_Buffer, m_BufferMemory, 0);
}

void CBuffer::CopyDataToBuffer(const VkDevice& Device, const void* data)
{
	void* mappedMemory;
	vkMapMemory(Device, m_BufferMemory, 0, BufferSize, 0, &mappedMemory);
	memcpy(mappedMemory, data, BufferSize);
	vkUnmapMemory(Device, m_BufferMemory);
}

void CBuffer::CopyBufferToBuffer(CBuffer& SourceBuffer, const CopyBufferToBufferParams& Params)
{
	const VkDevice& device = Params.m_LogicalDevice.GetLogicalDevice();

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = Params.m_CommandPool;
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;
	vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(commandBuffer, &beginInfo);

	VkBufferCopy copyRegion = {};
	copyRegion.srcOffset = 0; // Optional
	copyRegion.dstOffset = 0; // Optional
	copyRegion.size = Params.m_Size;
	vkCmdCopyBuffer(commandBuffer, SourceBuffer.GetBuffer(), m_Buffer, 1, &copyRegion);

	vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	const VkQueue& graphicsQueue = Params.m_LogicalDevice.GetGraphicsQueue();
	vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
	vkQueueWaitIdle(graphicsQueue);

	vkFreeCommandBuffers(device, Params.m_CommandPool, 1, &commandBuffer);
}

void CBuffer::Release(const VkDevice& Device)
{
	vkDestroyBuffer(Device, m_Buffer, nullptr);
	vkFreeMemory(Device, m_BufferMemory, nullptr);
	m_BufferReleased = true;
}

CBuffer::~CBuffer()
{
	ENG_ASSERT(m_BufferReleased, "Buffer was not released");
}

VkBuffer& CBuffer::GetBuffer()
{
	return m_Buffer;
}

void CBuffer::BindBuffer(const VkCommandBuffer& CommandBuffer)
{
	VkBuffer vertexBuffers[] = { m_Buffer };
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(CommandBuffer, 0, 1, vertexBuffers, offsets);
}

void CBuffer::DrawBuffer(const VkCommandBuffer& CommandBuffer)
{
	vkCmdDraw(CommandBuffer, BufferSize, 1, 0, 0);
}
