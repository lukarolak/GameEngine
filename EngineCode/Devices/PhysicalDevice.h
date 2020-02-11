#pragma once
#include <vulkan/vulkan_core.h>
#include <TypeDefs/TypeDefs.h>
#include <Queues/QueueFamilyIndices.h>
#include <vector>
class CPhysicalDevice
{
public:
	void PickPhysicalDevice(VkInstance Instance, const VkSurfaceKHR& Surface);
	const QueueFamilyIndices& GetQueueFamilyIndices() const;
	VkPhysicalDevice GetPhysicalDevice() const;
	const std::vector<const char*>& GetDeviceExtentions() const;
	engIntU32 GetMemoryType(engIntU32 Filter, VkMemoryPropertyFlags Properties) const;
private:
	bool IsDeviceSuitable(VkPhysicalDevice Device, const VkSurfaceKHR& Surface);
	bool CheckDeviceExtensionSupport(VkPhysicalDevice Device);

private:
	VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
	QueueFamilyIndices m_QueueFamilyIndices;
	const std::vector<const char*> m_DeviceExtensions = 
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};
};