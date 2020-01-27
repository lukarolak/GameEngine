#pragma once
#include <vulkan/vulkan_core.h>
#include <Devices/PhysicalDevice.h>
#include <Debuging/Validation.h>
class CLogicalDevice
{
public:
	void CreateLogicalDevice(const CPhysicalDevice& PhysicalDevice, const CValidation& ValidationLayers);
	void Release();
	const VkDevice GetLogicalDevice() const;
private:
	VkDevice m_Device;
	VkQueue m_GraphicsQueue;
	VkQueue m_PresentQueue;
};
