#pragma once
#include <vulkan/vulkan_core.h>
#include <vector>
class CCreateFrameBuffersParams
{
public:
	CCreateFrameBuffersParams(
		const std::vector<VkImageView>& ImageViews,
		const VkRenderPass& RenderPass,
		const VkExtent2D& SwapChainExtent,
		const VkDevice& Device);

public:
	const const std::vector<VkImageView>& m_ImageViews;
	const VkRenderPass& m_RenderPass;
	const VkExtent2D& m_SwapChainExtent;
	const VkDevice& m_Device;
};
