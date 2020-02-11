#pragma once
#include <VertexBuffer/Vertex.h>
#include <vector>
#include <Devices/PhysicalDevice.h>
class CVertexBuffer
{
public:
	void CreateVertexBuffer(const VkDevice& LogicalDevice, const CPhysicalDevice& PhysicalDevice);
	void Release(const VkDevice& Device);
	void BindVertexBuffer(const VkCommandBuffer& CommandBuffer);
	void DrawVertexBuffer(const VkCommandBuffer& CommandBuffer);
private:
	std::vector<CVertex> m_Vertices;
	VkBuffer m_VertexBuffer;
	VkDeviceMemory m_VertexBufferMemory;
};