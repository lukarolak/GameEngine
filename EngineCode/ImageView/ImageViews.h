#pragma once

#include <ImageView/CreateImageViewsParams.h>
class CImageViews
{
public:
	void CreateImageViews(const CreateImageViewsParams& Params);
	void Release(const VkDevice& LogicalDevice);
	const std::vector<VkImageView>& GetSwapChainImageViews() const;
private:
	std::vector<VkImageView> m_SwapChainImageViews;
};