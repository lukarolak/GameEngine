#include <Vertex/Vertex.h>

CVertex::CVertex(const engVector2& Position, const engVector3& Color)
	: m_Position(Position), m_Color(Color)
{
}

VkVertexInputBindingDescription CVertex::GetBindingDescription()
{
	VkVertexInputBindingDescription bindingDescription = {};
	bindingDescription.binding = 0;
	bindingDescription.stride = sizeof(CVertex);
	bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;


	return bindingDescription;
}

std::array<VkVertexInputAttributeDescription, 2> CVertex::GetAttributeDescriptions()
{
	std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};
	attributeDescriptions[0].binding = 0;
	attributeDescriptions[0].location = 0;
	attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
	attributeDescriptions[0].offset = offsetof(CVertex, m_Position);

	attributeDescriptions[1].binding = 0;
	attributeDescriptions[1].location = 1;
	attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDescriptions[1].offset = offsetof(CVertex, m_Color);

	return attributeDescriptions;
}
