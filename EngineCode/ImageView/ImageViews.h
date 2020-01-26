#pragma once

#include <ImageView/CreateImageViewsParams.h>
class ImageViews
{
public:
	void CreateImageViews(const CreateImageViewsParams& Params);
	void Release(const VkDevice& LogicalDevice);
private:
	std::vector<VkImageView> swapChainImageViews;
};