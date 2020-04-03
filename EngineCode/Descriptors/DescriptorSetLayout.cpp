#include <Descriptors/DescriptorSetLayout.h>
#include <Debuging/Assert.h>
void CDescriptorSetLayout::CreateDescriptorSetLayout(const VkDevice& Device)
{
    VkDescriptorSetLayoutBinding uboLayoutBinding = {};
    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uboLayoutBinding.descriptorCount = 1;
    uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    uboLayoutBinding.pImmutableSamplers = nullptr; // Optional

    VkDescriptorSetLayoutCreateInfo layoutInfo = {};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = 1;
    layoutInfo.pBindings = &uboLayoutBinding;

    if (vkCreateDescriptorSetLayout(Device, &layoutInfo, nullptr, &m_DescriptorSetLayout) != VK_SUCCESS)
    {
        ENG_ASSERT(false, "failed to create descriptor set layout!");
    }
}

const VkDescriptorSetLayout& CDescriptorSetLayout::GetDescriptorSetLayout()
{
    return m_DescriptorSetLayout;
}

void CDescriptorSetLayout::Release(const VkDevice& Device)
{
    vkDestroyDescriptorSetLayout(Device, m_DescriptorSetLayout, nullptr);
}
