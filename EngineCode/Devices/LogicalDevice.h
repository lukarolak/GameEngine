#pragma once
#include <vulkan/vulkan_core.h>
#include <Devices/PhysicalDevice.h>
#include <Debuging/Validation.h>
#include <Synchronization/SynchronizationObjectsGroup.h>
class CLogicalDevice
{
public:
	void CreateLogicalDevice(const CPhysicalDevice& PhysicalDevice, const CValidation& ValidationLayers);
	void Release();
	const VkDevice GetLogicalDevice() const;
	const VkQueue& GetGraphicsQueue() const;
	const VkQueue& GetPresentQueue() const;
	const CSynchronizationObjectsGroup& GetSynchronizationObjectsGroup() const;
	void SetImageInUse(const engIntU32 FrameIndex);
	void WaitForDeviceIdle() const;
private:
	VkDevice m_Device;
	VkQueue m_GraphicsQueue;
	VkQueue m_PresentQueue;
	CSynchronizationObjectsGroup m_SynchronizationObjectGroup;
};
