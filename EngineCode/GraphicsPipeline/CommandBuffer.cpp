#include <GraphicsPipeline/CommandBuffer.h>
#include <stdexcept>
#include <TypeDefs/TypeDefs.h>
void CCommandBuffer::CreateCommandBuffers(const CCreateCommandBufferParams& Params)
{
	const VkDevice& device = Params.m_LogicalDevice.GetLogicalDevice();

	std::vector<CVertex> vertices = {
	{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
	{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
	{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
	{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
	};
	std::vector<uint16_t> indices = {
	0, 1, 2, 2, 3, 0
	};

	VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

	CopyBufferToBufferParams copyBufferToBufferParams(bufferSize, Params.m_CommandPool, Params.m_LogicalDevice);
	CCreateVertexBufferParams createVertexBufferParams(vertices, device, Params.m_PhysicalDevice, copyBufferToBufferParams);
	m_VertexBuffer.CreateVertexBuffer(createVertexBufferParams);
	m_CommandBuffers.resize(Params.m_SwapChainFrameBuffers.size());

	CCreateIndexBufferParams createIndexBufferParams(indices, Params.m_LogicalDevice, Params.m_PhysicalDevice, Params.m_CommandPool);
	m_IndexBuffer.CreateIndexBuffer(createIndexBufferParams);

	VkCommandBufferAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = Params.m_CommandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = (uint32_t)m_CommandBuffers.size();

	if (vkAllocateCommandBuffers(device, &allocInfo, m_CommandBuffers.data()) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to allocate command buffers!");
	}

	for (engIntU32 i = 0; i < m_CommandBuffers.size(); i++) 
	{
		VkCommandBuffer& commandBuffer = m_CommandBuffers[i];

		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = 0; // Optional
		beginInfo.pInheritanceInfo = nullptr; // Optional

		if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to begin recording command buffer!");
		}

		VkRenderPassBeginInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = Params.m_RenderPass;
		renderPassInfo.framebuffer = Params.m_SwapChainFrameBuffers[i];
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = Params.m_SwapChainExtent;
		VkClearValue clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, Params.m_GraphicsPipeline);

		m_VertexBuffer.BindBuffer(commandBuffer);
		m_IndexBuffer.BindBuffer(commandBuffer);
		
		m_IndexBuffer.DrawBuffer(commandBuffer);

		vkCmdEndRenderPass(commandBuffer);

		if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to record command buffer!");
		}
	}
}

const std::vector<VkCommandBuffer>& CCommandBuffer::GetCommandBuffers() const
{
	return m_CommandBuffers;
}

void CCommandBuffer::Release(const VkDevice& Device)
{
	m_VertexBuffer.Release(Device);
	m_IndexBuffer.Release(Device);
}
