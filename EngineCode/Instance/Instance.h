#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <Debuging/Validation.h>
#include <Devices/PhysicalDevice.h>
#include <Devices/LogicalDevice.h>
#include <Window/WindowSurface.h>
#include <Window/Window.h>
#include <SwapChain/SwapChain.h>
class CInstance
{
public:
	VkInstance GetInstance() const;
	void CreateInstance(const EngWindow& Window);
	void Release();
	const CSwapChain& GetSwapChain() const;
	const CPhysicalDevice& GetPhysicalDevice() const;
	void DrawFrame(const EngWindow& Window);
	void RecreateSwapChainOnNextDrawCall();
private:
	VkInstance m_Instance;
	CValidation m_Validation;
	CPhysicalDevice m_PhysicalDevice;
	CWindowSurface m_surface;
	CSwapChain m_SwapChain;
};