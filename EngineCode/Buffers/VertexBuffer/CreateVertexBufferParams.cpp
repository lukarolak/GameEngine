#include "CreateVertexBufferParams.h"

CCreateVertexBufferParams::CCreateVertexBufferParams(std::vector<CVertex>& Data, const VkDevice& LogicalDevice, const CPhysicalDevice& PhysicalDevice, const CopyBufferToBufferParams& CopyBufferToBufferParams)
	: m_Data(Data)
	, m_LogicalDevice(LogicalDevice)
	, m_PhysicalDevice(PhysicalDevice)
	, m_CopyBufferToBufferParams(CopyBufferToBufferParams)
{
}
