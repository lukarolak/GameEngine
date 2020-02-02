#include "CreateGraphicsPipelineParams.h"

CreateGraphicsPipelineParams::CreateGraphicsPipelineParams(const VkDevice LogicalDevice, const VkExtent2D& SwapChainExtent, const VkRenderPass& RenderPass)
	: m_LogicalDevice(LogicalDevice)
	, m_SwapChainExtent(SwapChainExtent)
	, m_RenderPass(RenderPass)
{
}
