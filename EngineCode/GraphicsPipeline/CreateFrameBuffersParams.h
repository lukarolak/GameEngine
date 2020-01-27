#pragma once
#include <ImageView/ImageViews.h>
#include <GraphicsPipeline/RenderPass.h>
#include <SwapChain/SwapChain.h>
#include <Devices/LogicalDevice.h>
class CCreateFrameBuffersParams
{
public:
	CCreateFrameBuffersParams(
		const CImageViews& ImageViews,
		const CRenderPass& RenderPass,
		const CSwapChain& SwapChain,
		const CLogicalDevice& LogicalDevice);

public:
	const CImageViews& m_ImageViews;
	const CRenderPass& m_RenderPass;
	const CSwapChain& m_SwapChain;
	const CLogicalDevice& m_LogicalDevice;
};
