#include "CopyBufferToBufferParams.h"

CopyBufferToBufferParams::CopyBufferToBufferParams(const VkDeviceSize& Size, const VkCommandPool& CommandPool, const CLogicalDevice& LogicalDevice)
	: m_Size(Size)
	, m_CommandPool(CommandPool)
	, m_LogicalDevice(LogicalDevice)
{
}
