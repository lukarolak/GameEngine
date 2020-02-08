#pragma once
#include <vulkan/vulkan_core.h>
#include <SwapChain/CreateSwapChainParams.h>
#include <ImageView/ImageViews.h>
#include <GraphicsPipeline/RenderPass.h>
#include <GraphicsPipeline/GraphicsPipeline.h>
#include <GraphicsPipeline/FrameBuffer.h>
#include <GraphicsPipeline/CommandPool.h>
#include <GraphicsPipeline/CommandBuffer.h>
#include <Devices/LogicalDevice.h>
class CSwapChain
{
public:
	void CreateSwapChain(const CreateSwapChainParams& Params);
	void Release();
	void DrawFrame();
private:
	void RecreateSwapChain(const CreateSwapChainParams& Params);
	void ReleaseSwapChainDependants();
	void CreateSwapChainDependants(const CreateSwapChainParams& Params);
private:
	VkSwapchainKHR m_SwapChain;
	std::vector<VkImage> m_SwapChainImages;
	VkFormat m_SwapChainImageFormat;
	VkExtent2D m_SwapChainExtent;
	CImageViews m_ImageViews;
	CRenderPass m_RenderPass;
	CGraphicsPipeline m_GraphicsPipeline;
	CFrameBuffer m_FrameBuffer;
	CCommandPool m_CommandPool;
	CCommandBuffer m_CommandBuffer;
	CLogicalDevice m_LogicalDevice;
	engIntU32 m_CurrentFrame = 0;
};