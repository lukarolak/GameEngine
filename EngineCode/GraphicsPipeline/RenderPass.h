#pragma once
#include <vulkan/vulkan_core.h>
class RenderPass
{
public:
	void CreateRenderPass(const VkFormat& SwapChainImageFormat, const VkDevice& LogicalDevice);
	void Release(const VkDevice& LogicalDevice);
	const VkRenderPass& GetRenderPass() const;
private:
	VkRenderPass m_RenderPass;
};