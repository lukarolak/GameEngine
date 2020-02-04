#pragma once
#include <vulkan/vulkan_core.h>
#include <SwapChain/CreateSwapChainParams.h>
#include <ImageView/ImageViews.h>
#include <GraphicsPipeline/RenderPass.h>
#include <GraphicsPipeline/GraphicsPipeline.h>
#include <GraphicsPipeline/FrameBuffer.h>
#include <GraphicsPipeline/CommandPool.h>
#include <GraphicsPipeline/CommandBuffer.h>
class CSwapChain
{
public:
	void CreateSwapChain(const CreateSwapChainParams& Params, const bool CreateCommandPool);
	void Release(const VkDevice& device, const bool ReleaseCommandPool);
	const std::vector<VkImage>& GetSwapChainImages() const;
	const VkFormat& GetSwapChainImageFormat() const;
	const VkExtent2D& GetSwapChainExtent() const;
	const VkSwapchainKHR& GetSwapChain() const;
	const CImageViews& GetImageViews() const;
	const CRenderPass& GetRenderPass() const;
	const CGraphicsPipeline& GetGraphicsPipeline() const;
	const CFrameBuffer& GetFrameBuffer() const;
	const CCommandBuffer& GetCommandBuffer() const;
	void RecreateSwapChain(const CreateSwapChainParams& Params);
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
};