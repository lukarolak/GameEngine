#pragma once
#include <vulkan/vulkan_core.h>
#include <Window/Window.h>
class CWindowSurface
{
public:
	void CreateSurface(GLFWwindow* Window, const VkInstance& Instance);
	void Release(const VkInstance& inInstance);
	const VkSurfaceKHR& GetSurface() const;
private:
	VkSurfaceKHR m_Surface;
};