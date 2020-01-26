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
class Instance
{
public:
	VkInstance GetInstance() const;
	void CreateInstance(const EngWindow& Window);
	void Release();
private:
	VkInstance m_Instance;
	Validation m_Validation;
	PhysicalDevice m_PhysicalDevice;
	LogicalDevice m_LogicalDevice;
	WindowSurface m_surface;
	SwapChain m_SwapChain;
	ImageViews m_ImageViews;
	GraphicsPipeline m_GraphicPipeline;
	RenderPass m_RenderPass;
};