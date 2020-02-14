#include <Devices\PhysicalDevice.h>
#include <stdexcept>
#include <vector>
#include <map>
#include <Queues/QueueFamilyIndices.h>
#include <set>
#include <SwapChain/SwapChainSupportDetails.h>
#include <Debuging/Assert.h>

void CPhysicalDevice::PickPhysicalDevice(VkInstance Instance, const VkSurfaceKHR& Surface)
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(Instance, &deviceCount, nullptr);

	ENG_ASSERT(deviceCount != 0, "failed to find GPUs with Vulkan support!");

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(Instance, &deviceCount, devices.data());

	// Use an ordered map to automatically sort candidates by increasing score
	std::multimap<int, VkPhysicalDevice> candidates;

	for (const auto& device : devices) 
	{
		if (IsDeviceSuitable(device, Surface))
		{
			m_PhysicalDevice = device;
			break;
		}
	}

	ENG_ASSERT(m_PhysicalDevice != VK_NULL_HANDLE, "failed to find a suitable GPU!");

	m_QueueFamilyIndices.InitQueueFamilyIndices(m_PhysicalDevice, Surface);
}

const QueueFamilyIndices& CPhysicalDevice::GetQueueFamilyIndices() const
{
	return m_QueueFamilyIndices;
}

VkPhysicalDevice CPhysicalDevice::GetPhysicalDevice() const
{
	return m_PhysicalDevice;
}

const std::vector<const char*>& CPhysicalDevice::GetDeviceExtentions() const
{
	return m_DeviceExtensions;
}

engIntU32 CPhysicalDevice::GetMemoryType(engIntU32 Filter, VkMemoryPropertyFlags Properties) const
{
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(m_PhysicalDevice, &memProperties);
	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
	{
		if ((Filter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & Properties) == Properties)
		{
			return i;
		}
	}
	ENG_ASSERT(false, "failed to find suitable memory type!");
	return 0;
}

bool CPhysicalDevice::IsDeviceSuitable(VkPhysicalDevice Device, const VkSurfaceKHR& Surface)
{
	QueueFamilyIndices indices;
	indices.InitQueueFamilyIndices(Device, Surface);
	bool extensionsSupported = CheckDeviceExtensionSupport(Device);

	bool swapChainAdequate = false;
	if (extensionsSupported)
	{
		SwapChainSupportDetails swapChainSupport;
		swapChainSupport.InitSwapChainSupportDetails(Device, Surface);
		swapChainAdequate = swapChainSupport.IsSwapChainAdequate();
	}

	return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

bool CPhysicalDevice::CheckDeviceExtensionSupport(VkPhysicalDevice Device)
{
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(Device, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(Device, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(m_DeviceExtensions.begin(), m_DeviceExtensions.end());

	for (const auto& extension : availableExtensions) 
	{
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}

