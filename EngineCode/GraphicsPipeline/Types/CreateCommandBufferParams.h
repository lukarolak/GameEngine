#pragma once
#include <vulkan/vulkan_core.h>
#include <vector>
class CCreateCommandBufferParams
{
public:
	CCreateCommandBufferParams(const VkCommandPool& CommandPool, const VkDevice& Device, const VkRenderPass& RenderPass, const std::vector<VkFramebuffer>& SwapChainFrameBuffers, const VkExtent2D& SwapChainExtent, const VkPipeline& GraphicsPipeline);
public:
	const VkCommandPool& m_CommandPool;
	const VkDevice& m_Device;
	const VkRenderPass& m_RenderPass;
	const std::vector<VkFramebuffer>& m_SwapChainFrameBuffers;
	const VkExtent2D& m_SwapChainExtent;
	const VkPipeline& m_GraphicsPipeline;
};