#pragma once
#include <vulkan/vulkan_core.h>
#include <vector>
#include <Devices/PhysicalDevice.h>
#include <Devices/LogicalDevice.h>
class CCreateCommandBufferParams
{
public:
	CCreateCommandBufferParams(const VkCommandPool& CommandPool, const CLogicalDevice& LogicalDevice, const VkRenderPass& RenderPass, const std::vector<VkFramebuffer>& SwapChainFrameBuffers, const VkExtent2D& SwapChainExtent, const VkPipeline& GraphicsPipeline, const CPhysicalDevice& PhysicalDevice);
public:
	const VkCommandPool& m_CommandPool;
	const CLogicalDevice& m_LogicalDevice;
	const VkRenderPass& m_RenderPass;
	const std::vector<VkFramebuffer>& m_SwapChainFrameBuffers;
	const VkExtent2D& m_SwapChainExtent;
	const VkPipeline& m_GraphicsPipeline;
	const CPhysicalDevice& m_PhysicalDevice;
};