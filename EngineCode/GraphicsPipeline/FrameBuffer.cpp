#include <GraphicsPipeline/FrameBuffer.h>
#include <stdexcept>
#include <TypeDefs/TypeDefs.h>
void CFrameBuffer::CreateFrameBuffers(const CCreateFrameBuffersParams& Params)
{
    swapChainFramebuffers.resize(Params.m_ImageViews.size());
    engIntU32 swapChainFrameBufferCounter = 0;
    for (const VkImageView& imageView : Params.m_ImageViews)
    {
        VkImageView attachments[] = 
        {
        imageView
        };

        VkFramebufferCreateInfo framebufferInfo = {};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = Params.m_RenderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        const VkExtent2D&  m_SwapChainExtent = Params.m_SwapChainExtent;
        framebufferInfo.width = m_SwapChainExtent.width;
        framebufferInfo.height = m_SwapChainExtent.height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(Params.m_Device, &framebufferInfo, nullptr, &swapChainFramebuffers[swapChainFrameBufferCounter]) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create framebuffer!");
        }
        swapChainFrameBufferCounter++;
    }
   
}

void CFrameBuffer::Release(const VkDevice& Device)
{
    for (const VkFramebuffer& frameBuffer : swapChainFramebuffers)
    {
        vkDestroyFramebuffer(Device, frameBuffer, nullptr);
    }
}

const std::vector<VkFramebuffer>& CFrameBuffer::GetSwapChainFrameBuffers() const
{
    return swapChainFramebuffers;
}
