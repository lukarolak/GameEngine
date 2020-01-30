#pragma once
#include <vulkan/vulkan_core.h>
#include <vector>
#include <GraphicsPipeline/CreateFrameBuffersParams.h>
class CFrameBuffer
{
public:
	void CreateFrameBuffers(const CCreateFrameBuffersParams& Params);
	void Release(const VkDevice& Device);
	const std::vector<VkFramebuffer>& GetSwapChainFrameBuffers() const;
private:
	std::vector<VkFramebuffer> swapChainFramebuffers;
};
