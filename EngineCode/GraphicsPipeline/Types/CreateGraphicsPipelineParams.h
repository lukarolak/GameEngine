#pragma once
#include <vulkan/vulkan_core.h>
class CreateGraphicsPipelineParams
{
public:
	CreateGraphicsPipelineParams(const VkDevice LogicalDevice, const VkExtent2D& SwapChainExtent, const VkRenderPass& RenderPass);
public:
	const VkDevice m_LogicalDevice;
	const VkExtent2D& m_SwapChainExtent;
	const VkRenderPass& m_RenderPass;
};