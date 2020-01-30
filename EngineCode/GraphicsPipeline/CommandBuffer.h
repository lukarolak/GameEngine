#pragma once
#include <vector>
#include <vulkan/vulkan_core.h>
#include <Instance/Instance.h>
class CCommandBuffer
{
public:
	void CreateCommandBuffers(const CInstance& Instance);
	const std::vector<VkCommandBuffer>& GetCommandBuffers() const;
private:
	std::vector<VkCommandBuffer> commandBuffers;
};