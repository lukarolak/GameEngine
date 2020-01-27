#include <ImageView/ImageViews.h>
#include <TypeDefs/TypeDefs.h>
#include <stdexcept>

void CImageViews::CreateImageViews(const CreateImageViewsParams& Params)
{
	m_SwapChainImageViews.resize(Params.m_Images.size());

	for (size_t i = 0; i < Params.m_Images.size(); i++)
	{
		VkImageViewCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = Params.m_Images[i];

		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = Params.m_ImageFormat;

		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;

		if (vkCreateImageView(Params.m_LogicalDevice, &createInfo, nullptr, &m_SwapChainImageViews[i]) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create image views!");
		}
	}
}

void CImageViews::Release(const VkDevice& LogicalDevice)
{
	for (auto imageView : m_SwapChainImageViews) 
	{
		vkDestroyImageView(LogicalDevice, imageView, nullptr);
	}
}

const std::vector<VkImageView>& CImageViews::GetSwapChainImageViews() const
{
	return m_SwapChainImageViews;
}
