#include <GraphicsPipeline/FrameBuffer.h>
#include <stdexcept>
void CFrameBuffer::CreateFrameBuffers(const CCreateFrameBuffersParams& Params)
{
    const std::vector<VkImageView>& imageViews = Params.m_ImageViews.GetSwapChainImageViews();
	
    swapChainFramebuffers.resize(imageViews.size());
    engIntU32 swapChainFrameBufferCounter = 0;
    for (const VkImageView& imageView : imageViews)
    {
        VkImageView attachments[] = 
        {
        imageView
        };

        VkFramebufferCreateInfo framebufferInfo = {};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = Params.m_RenderPass.GetRenderPass();
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        const VkExtent2D&  swapChainExtent = Params.m_SwapChain.GetSwapChainExtent();
        framebufferInfo.width = swapChainExtent.width;
        framebufferInfo.height = swapChainExtent.height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(Params.m_LogicalDevice.GetLogicalDevice(), &framebufferInfo, nullptr, &swapChainFramebuffers[swapChainFrameBufferCounter]) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create framebuffer!");
        }
        swapChainFrameBufferCounter++;
    }
   
}

void CFrameBuffer::Release(const CLogicalDevice& LogicalDevice)
{
    for (const VkFramebuffer& frameBuffer : swapChainFramebuffers)
    {
        vkDestroyFramebuffer(LogicalDevice.GetLogicalDevice(), frameBuffer, nullptr);
    }
}

const std::vector<VkFramebuffer>& CFrameBuffer::GetSwapChainFrameBuffers() const
{
    return swapChainFramebuffers;
}
