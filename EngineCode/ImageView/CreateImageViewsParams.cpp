#include "CreateImageViewsParams.h"

CreateImageViewsParams::CreateImageViewsParams(const std::vector<VkImage>& Images, const VkFormat& ImageFormat, const VkDevice& LogicalDevice)
	: m_Images(Images)
	, m_ImageFormat(ImageFormat)
	, m_LogicalDevice(LogicalDevice)
{
}
