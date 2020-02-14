#pragma once
#include <vulkan/vulkan_core.h>
#include <vector>
#include <Window/Resolution.h>
#include <GLFW/glfw3.h>
class SwapChainSupportDetails
{
public:
    void InitSwapChainSupportDetails(const VkPhysicalDevice Device, const VkSurfaceKHR& Surface);
    bool IsSwapChainAdequate();
    VkSurfaceFormatKHR GetOptimalSwapSurfaceFormat();
    VkPresentModeKHR GetOptimalSwapPresentMode();
    VkExtent2D SwapChainSupportDetails::GetOptimalSwapChainExtent(GLFWwindow* Window);
    const VkSurfaceCapabilitiesKHR& GetCapabilities();
private:
    VkSurfaceCapabilitiesKHR m_Capabilities;
    std::vector<VkSurfaceFormatKHR> m_Formats;
    std::vector<VkPresentModeKHR> m_PresentModes;
    bool SwapChainSupportDetailsInited = false;
};