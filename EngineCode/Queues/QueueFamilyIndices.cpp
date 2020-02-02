#include <Queues/QueueFamilyIndices.h>
#include <vector>
#include <Debuging/Assert.h>
void QueueFamilyIndices::InitQueueFamilyIndices(VkPhysicalDevice Device, const VkSurfaceKHR& Surface)
{
	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(Device, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(Device, &queueFamilyCount, queueFamilies.data());

	engIntU32 i = 0;
	for (const auto& queueFamily : queueFamilies)
	{
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			m_graphicsFamily = i;
		}

		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(Device, i, Surface, &presentSupport);

		if (presentSupport)
		{
			m_presentFamily = i;
		}

		if (isComplete())
		{
			break;
		}

		i++;
	}
	QueueFamilyIndicesInited = true;
}

const std::optional<engIntU32>& QueueFamilyIndices::GetGraphicsFamily() const
{
	ENG_ASSERT(QueueFamilyIndicesInited);
	return m_graphicsFamily;
}

const std::optional<engIntU32>& QueueFamilyIndices::GetPresentFamily() const
{
	ENG_ASSERT(QueueFamilyIndicesInited);
	return m_presentFamily;
}
