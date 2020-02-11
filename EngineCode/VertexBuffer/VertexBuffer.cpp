#include "VertexBuffer.h"
#include <vulkan/vulkan_core.h>
void CVertexBuffer::CreateVertexBuffer(const VkDevice& LogicalDevice, const CPhysicalDevice& PhysicalDevice)
{
	m_Vertices = 
	{{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
	{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
	{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}};

	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = sizeof(m_Vertices[0]) * m_Vertices.size();
	bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(LogicalDevice, &bufferInfo, nullptr, &m_VertexBuffer) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create vertex buffer!");
	}

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(LogicalDevice, m_VertexBuffer, &memRequirements);

	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = PhysicalDevice.GetMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	if (vkAllocateMemory(LogicalDevice, &allocInfo, nullptr, &m_VertexBufferMemory) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to allocate vertex buffer memory!");
	}

	vkBindBufferMemory(LogicalDevice, m_VertexBuffer, m_VertexBufferMemory, 0);

	void* data;
	vkMapMemory(LogicalDevice, m_VertexBufferMemory, 0, bufferInfo.size, 0, &data);
	memcpy(data, m_Vertices.data(), (size_t)bufferInfo.size);
	vkUnmapMemory(LogicalDevice, m_VertexBufferMemory);
}

void CVertexBuffer::Release(const VkDevice& Device)
{
	vkDestroyBuffer(Device, m_VertexBuffer, nullptr);
	vkFreeMemory(Device, m_VertexBufferMemory, nullptr);
}

void CVertexBuffer::BindVertexBuffer(const VkCommandBuffer& CommandBuffer)
{
	VkBuffer vertexBuffers[] = { m_VertexBuffer };
	VkDeviceSize offsets[] = { 0 };
	vkCmdBindVertexBuffers(CommandBuffer, 0, 1, vertexBuffers, offsets);
}

void CVertexBuffer::DrawVertexBuffer(const VkCommandBuffer& CommandBuffer)
{
	vkCmdDraw(CommandBuffer, static_cast<engIntU32>(m_Vertices.size()), 1, 0, 0);
}
