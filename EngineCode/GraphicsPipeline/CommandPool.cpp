#include <GraphicsPipeline/CommandPool.h>
#include <stdexcept>
#include <Debuging/Assert.h>
void CCommandPool::CreateCommandPool(const engIntU32& GraphicsFamily, const VkDevice& LogicalDevice)
{
	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = GraphicsFamily;
	poolInfo.flags = 0; // Optional

	VkResult result;
	result = vkCreateCommandPool(LogicalDevice, &poolInfo, nullptr, &commandPool);
	ENG_ASSERT(result == VK_SUCCESS, "failed to create command pool!");
}

void CCommandPool::Release(const VkDevice& Device)
{
	vkDestroyCommandPool(Device, commandPool, nullptr);
}

const VkCommandPool& CCommandPool::GetCommandPool() const
{
	return commandPool;
}
