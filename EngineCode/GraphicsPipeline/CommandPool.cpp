#include <GraphicsPipeline/CommandPool.h>
#include <stdexcept>

void CCommandPool::CreateCommandPool(const CPhysicalDevice& PhysicalDevice, const CLogicalDevice& LogicalDevice)
{
	const QueueFamilyIndices& queueFamilyIndices = PhysicalDevice.GetQueueFamilyIndices();;

	VkCommandPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.queueFamilyIndex = queueFamilyIndices.GetGraphicsFamily().value();
	poolInfo.flags = 0; // Optional

	if (vkCreateCommandPool(LogicalDevice.GetLogicalDevice(), &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create command pool!");
	}
}

void CCommandPool::Release(const CLogicalDevice& LogicalDevice)
{
	vkDestroyCommandPool(LogicalDevice.GetLogicalDevice(), commandPool, nullptr);
}

const VkCommandPool& CCommandPool::GetCommandPool() const
{
	return commandPool;
}
