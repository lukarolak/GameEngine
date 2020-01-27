#pragma once
#include <vulkan/vulkan_core.h>
#include <SwapChain/CreateSwapChainParams.h>
class CSwapChain
{
public:
	void CreateSwapChain(const CreateSwapChainParams& Params);
	void Release(const VkDevice& device);
	const std::vector<VkImage>& GetSwapChainImages() const;
	const VkFormat& GetSwapChainImageFormat() const;
	const VkExtent2D& GetSwapChainExtent() const;
private:
	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
};