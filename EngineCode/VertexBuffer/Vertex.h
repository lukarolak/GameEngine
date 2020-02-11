#pragma once
#include <Math/Vector/Vector.h>
#include <vulkan/vulkan_core.h>
#include <array>
class CVertex
{
public:
	CVertex() = default;
	CVertex(const engVector2& Position, const engVector3& Color);
	static VkVertexInputBindingDescription GetBindingDescription();
	static std::array<VkVertexInputAttributeDescription, 2> GetAttributeDescriptions();
private:
	engVector2 m_Position;
	engVector3 m_Color;
};