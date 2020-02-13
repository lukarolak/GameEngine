#include "CreateBufferParams.h"

CCreateBufferParams::CCreateBufferParams(const VkDevice& LogicalDevice, const CPhysicalDevice& PhysicalDevice, const engIntU32& Size, const VkBufferUsageFlags& Usage, const VkMemoryPropertyFlags& Properties)
	: m_LogicalDevice(LogicalDevice)
	, m_PhysicalDevice(PhysicalDevice)
	, m_Size(Size)
	, m_Usage(Usage)
	, m_Properties(Properties)
{
}
