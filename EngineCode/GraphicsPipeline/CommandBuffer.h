#pragma once
#include <vector>
#include <vulkan/vulkan_core.h>
#include <GraphicsPipeline/Types/CreateCommandBufferParams.h>
class CCommandBuffer
{
public:
	void CreateCommandBuffers(const CCreateCommandBufferParams& Params);
	const std::vector<VkCommandBuffer>& GetCommandBuffers() const;
private:
	std::vector<VkCommandBuffer> commandBuffers;
};