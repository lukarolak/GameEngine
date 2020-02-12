#pragma once
#include <Buffers/CopyBufferToBufferParams.h>
#include <vector>
#include <Vertex/Vertex.h>
#include <Devices/PhysicalDevice.h>
class CCreateVertexBufferParams
{
public:
	CCreateVertexBufferParams(std::vector<CVertex>& Data, const VkDevice& LogicalDevice, const CPhysicalDevice& PhysicalDevice, const CopyBufferToBufferParams& CopyBufferToBufferParams);

public:
	std::vector<CVertex>& m_Data;
	const VkDevice& m_LogicalDevice;
	const CPhysicalDevice& m_PhysicalDevice;
	const CopyBufferToBufferParams& m_CopyBufferToBufferParams;
};