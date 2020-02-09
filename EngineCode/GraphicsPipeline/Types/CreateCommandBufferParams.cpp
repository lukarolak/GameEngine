#include <GraphicsPipeline/Types/CreateCommandBufferParams.h>

CCreateCommandBufferParams::CCreateCommandBufferParams(const VkCommandPool& CommandPool, const VkDevice& Device, const VkRenderPass& RenderPass, const std::vector<VkFramebuffer>& SwapChainFrameBuffers, const VkExtent2D& SwapChainExtent, const VkPipeline& GraphicsPipeline)
	:  m_CommandPool(CommandPool)
    ,   m_Device(Device)
    ,   m_RenderPass(RenderPass)
    ,   m_SwapChainFrameBuffers(SwapChainFrameBuffers)
    ,   m_SwapChainExtent(SwapChainExtent)
    ,   m_GraphicsPipeline(GraphicsPipeline)
{
}
