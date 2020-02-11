#pragma once
#include <vector>
#include <vulkan/vulkan_core.h>
#include <GraphicsPipeline/Types/CreateCommandBufferParams.h>
#include <VertexBuffer/VertexBuffer.h>
class CCommandBuffer
{
public:
	void CreateCommandBuffers(const CCreateCommandBufferParams& Params);
	const std::vector<VkCommandBuffer>& GetCommandBuffers() const;
	void Release(const VkDevice& Device);
private:
	std::vector<VkCommandBuffer> m_CommandBuffers;
	CVertexBuffer m_VertexBuffer;
};