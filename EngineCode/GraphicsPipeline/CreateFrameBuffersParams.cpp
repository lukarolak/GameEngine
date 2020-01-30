#include "CreateFrameBuffersParams.h"

CCreateFrameBuffersParams::CCreateFrameBuffersParams(
	const std::vector<VkImageView>& ImageViews,
	const VkRenderPass& RenderPass,
	const VkExtent2D& SwapChainExtent,
	const VkDevice& Device)
	: m_ImageViews(ImageViews)
	, m_RenderPass(RenderPass)
	, m_SwapChainExtent(SwapChainExtent)
	, m_Device(Device)
{
}
