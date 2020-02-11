#include <Devices/LogicalDevice.h>
#include <Queues/QueueFamilyIndices.h>
#include <Debuging/Validation.h>
#include <stdexcept>
#include <set>
#include <Debuging/Assert.h>
void CLogicalDevice::CreateLogicalDevice(const CPhysicalDevice& PhysicalDevice, const CValidation& ValidationLayers)
{
	QueueFamilyIndices indices = PhysicalDevice.GetQueueFamilyIndices();

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<uint32_t> uniqueQueueFamilies = { indices.GetGraphicsFamily().value(), indices.GetPresentFamily().value() };

	float queuePriority = 1.0f;
	for (uint32_t queueFamily : uniqueQueueFamilies) {
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	VkPhysicalDeviceFeatures deviceFeatures = {};
	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.pEnabledFeatures = &deviceFeatures;
	const std::vector<const char*>& deviceExtensions = PhysicalDevice.GetDeviceExtentions();
	createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = deviceExtensions.data();

	if (ValidationLayers.GetValidationLayersEnabled())
	{
		const std::vector<const char*>& validationLayers = ValidationLayers.GetValidationLayers();
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}

	if (vkCreateDevice(PhysicalDevice.GetPhysicalDevice(), &createInfo, nullptr, &m_Device) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create logical device!");
	}

	vkGetDeviceQueue(m_Device, indices.GetGraphicsFamily().value(), 0, &m_GraphicsQueue);
	vkGetDeviceQueue(m_Device, indices.GetPresentFamily().value(), 0, &m_PresentQueue);

	m_SynchronizationObjectGroup.CreateSynchronizationObjectsGroup(m_Device);
}

void CLogicalDevice::Release()
{
	m_SynchronizationObjectGroup.Release(m_Device);
	vkDestroyDevice(m_Device, nullptr);
}

const VkDevice CLogicalDevice::GetLogicalDevice() const
{
	return m_Device;
}

const VkQueue& CLogicalDevice::GetGraphicsQueue() const
{
	return m_GraphicsQueue;
}

const VkQueue& CLogicalDevice::GetPresentQueue() const
{
	return m_PresentQueue;
}

const CSynchronizationObjectsGroup& CLogicalDevice::GetSynchronizationObjectsGroup() const
{
	return m_SynchronizationObjectGroup;
}

void CLogicalDevice::SetImageInUse(const engIntU32 FrameIndex)
{
	m_SynchronizationObjectGroup.SetImageInUse(FrameIndex);
}

void CLogicalDevice::WaitForDeviceIdle() const
{
	vkDeviceWaitIdle(m_Device);
}
