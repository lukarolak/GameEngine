#include "CreateFrameBuffersParams.h"

CCreateFrameBuffersParams::CCreateFrameBuffersParams(const CImageViews& ImageViews, const CRenderPass& RenderPass, const CSwapChain& SwapChain, const CLogicalDevice& LogicalDevice)
	: m_ImageViews(ImageViews)
	, m_RenderPass(RenderPass)
	, m_SwapChain(SwapChain)
	, m_LogicalDevice(LogicalDevice)
{
}
