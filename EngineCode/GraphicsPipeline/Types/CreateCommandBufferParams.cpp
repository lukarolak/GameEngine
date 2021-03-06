#include <GraphicsPipeline/Types/CreateCommandBufferParams.h>

CCreateCommandBufferParams::CCreateCommandBufferParams(const VkCommandPool& CommandPool, const CLogicalDevice& LogicalDevice, const VkRenderPass& RenderPass, const std::vector<VkFramebuffer>& SwapChainFrameBuffers, const VkExtent2D& SwapChainExtent, const VkPipeline& GraphicsPipeline, const CPhysicalDevice& PhysicalDevice)
    : m_CommandPool(CommandPool)
    , m_LogicalDevice(LogicalDevice)
    , m_RenderPass(RenderPass)
    , m_SwapChainFrameBuffers(SwapChainFrameBuffers)
    , m_SwapChainExtent(SwapChainExtent)
    , m_GraphicsPipeline(GraphicsPipeline)
    , m_PhysicalDevice(PhysicalDevice)
{
}
