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
	void DrawFrame(const CreateSwapChainParams& Params);
	void RecreateSwapChainOnNextDrawCall();
private:
	enum class SwapChainMember
	{
		SwapChain,
		ImageViews,
		RenderPass,
		GraphicsPipeline,
		FrameBuffer,
		CommandBuffer,
		LogicalDevice,
		CommandPool,
	};
	void RecreateSwapChain(const CreateSwapChainParams& Params);
	void ReleaseSwapChainMember(const SwapChainMember member);
	void CreateSwapChainMember(const CreateSwapChainParams& Params,const SwapChainMember member);
	void WaitForValidFrameBufferSize(GLFWwindow* Window, const VkDevice& Device);
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
	bool m_RecreateSwapChain = false;
};