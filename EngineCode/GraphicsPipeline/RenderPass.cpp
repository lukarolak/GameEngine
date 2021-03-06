#include <GraphicsPipeline/RenderPass.h>
#include <stdexcept>
#include <Debuging/Assert.h>
void CRenderPass::CreateRenderPass(const VkFormat& SwapChainImageFormat, const VkDevice& LogicalDevice)
{
    VkAttachmentDescription colorAttachment = {};
    colorAttachment.format = SwapChainImageFormat;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorAttachmentRef = {};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass = {};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;

    VkRenderPassCreateInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;

    VkResult result;
    result = vkCreateRenderPass(LogicalDevice, &renderPassInfo, nullptr, &m_RenderPass);
    ENG_ASSERT(result == VK_SUCCESS, "failed to create render pass!");
}

void CRenderPass::Release(const VkDevice& LogicalDevice)
{
    vkDestroyRenderPass(LogicalDevice, m_RenderPass, nullptr);
}

const VkRenderPass& CRenderPass::GetRenderPass() const
{
    return m_RenderPass;
}
