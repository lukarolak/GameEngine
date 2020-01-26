#pragma once
#include <TypeDefs/TypeDefs.h>
#include <optional>
#include <vulkan/vulkan_core.h>
class QueueFamilyIndices
{
public:
	void InitQueueFamilyIndices(VkPhysicalDevice Device, const VkSurfaceKHR& Surface);
	bool isComplete() 
	{
		return m_graphicsFamily.has_value() && m_presentFamily.has_value();
	}
	const std::optional<engIntU32>& GetGraphicsFamily() const;
	const std::optional<engIntU32>& GetPresentFamily() const;
private:
	std::optional<engIntU32> m_graphicsFamily;
	std::optional<engIntU32> m_presentFamily;
	bool QueueFamilyIndicesInited = false;
};