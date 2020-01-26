#pragma once
#include <vector>
#include <vulkan/vulkan_core.h>
class CreateImageViewsParams
{
public:
	CreateImageViewsParams(const std::vector<VkImage>& Images, const VkFormat& ImageFormat, const VkDevice& LogicalDevice);
public:
	const std::vector<VkImage>& m_Images;
	const VkFormat& m_ImageFormat;
	const VkDevice& m_LogicalDevice;
};
