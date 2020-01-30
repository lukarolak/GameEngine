#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <Debuging/Validation.h>
#include <Devices/PhysicalDevice.h>
#include <Devices/LogicalDevice.h>
#include <Window/WindowSurface.h>
#include <Window/Window.h>
#include <SwapChain/SwapChain.h>
#include <ImageView/ImageViews.h>
#include <GraphicsPipeline/GraphicsPipeline.h>
#include <GraphicsPipeline/RenderPass.h>
#include <GraphicsPipeline/FrameBuffer.h>
#include <GraphicsPipeline/CommandPool.h>
class CInstance
{
public:
	VkInstance GetInstance() const;
	void CreateInstance(const EngWindow& Window);
	void Release();
	const CGraphicsPipeline& GetGraphicsPipeline() const;
	const CSwapChain& GetSwapChain() const;
	const CRenderPass& GetRenderPass() const;
	const CLogicalDevice& GetLogicalDevice() const;
	const CPhysicalDevice& GetPhysicalDevice() const;
	const CFrameBuffer& GetFrameBuffer() const;
	const CCommandPool& GetCommandPool() const;
	void SetImageInUse(const engIntU32 FrameIndex);
private:
	VkInstance m_Instance;
	CValidation m_Validation;
	CPhysicalDevice m_PhysicalDevice;
	CLogicalDevice m_LogicalDevice;
	CWindowSurface m_surface;
	CSwapChain m_SwapChain;
	CImageViews m_ImageViews;
	CGraphicsPipeline m_GraphicPipeline;
	CRenderPass m_RenderPass;
	CFrameBuffer m_FrameBuffer;
	CCommandPool m_CommandPool;
};