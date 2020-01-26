#pragma once
#include <vulkan/vulkan_core.h>
#include <vector>
#include <Window/Resolution.h>
class SwapChainSupportDetails
{
public:
    void InitSwapChainSupportDetails(const VkPhysicalDevice Device, const VkSurfaceKHR& Surface);
    bool IsSwapChainAdequate();
    VkSurfaceFormatKHR GetOptimalSwapSurfaceFormat();
    VkPresentModeKHR GetOptimalSwapPresentMode();
    VkExtent2D GetOptimalSwapExtent(const WindowResolution& Resolution);
    const VkSurfaceCapabilitiesKHR& GetCapabilities();
private:
    VkSurfaceCapabilitiesKHR m_Capabilities;
    std::vector<VkSurfaceFormatKHR> m_Formats;
    std::vector<VkPresentModeKHR> m_PresentModes;
    bool SwapChainSupportDetailsInited = false;
};