#pragma once
#include <vector>
#include <Devices/LogicalDevice.h>
template <typename DataType>
class CCreateIndexBufferParams
{
public:
	CCreateIndexBufferParams(const std::vector<DataType>& Data, const CLogicalDevice& LogicalDevice, const CPhysicalDevice& PhysicalDevice, const VkCommandPool& CommandPool)
		: m_Data(Data)
		, m_LogicalDevice(LogicalDevice)
		, m_PhysicalDevice(PhysicalDevice)
		, m_CommandPool(CommandPool)
	{}

public:
	const std::vector<DataType>& m_Data;
	const CLogicalDevice& m_LogicalDevice;
	const CPhysicalDevice& m_PhysicalDevice;
	const VkCommandPool& m_CommandPool;
};