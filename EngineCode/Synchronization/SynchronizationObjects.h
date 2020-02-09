#pragma once
#include <vulkan/vulkan_core.h>
#include <TypeDefs/TypeDefs.h>
class CSynchronizationObjects
{
public:
	void CreateSynchronnizationObjects(const VkDevice& Device);
	const VkSemaphore& GetImageAvailableSemaphore() const;
	const VkSemaphore& GetRenderFinishedSemaphore() const;
	const VkFence& GetInFlightFence() const;
	const VkFence& GetImageInFlightFence() const;
	void SetImageInFlight(const VkFence& Fence);
	void Release(const VkDevice& Device);
	void SetImageInUse();
	void RecreateSynchronizationObjects(const VkDevice& Device);
private:
	VkSemaphore m_ImageAvailableSemaphore;
	VkSemaphore m_RenderFinishedSemaphore;
	VkFence m_InFlightFence;
	VkFence m_ImageInFlight = VK_NULL_HANDLE;
	bool m_SynchronizationObjectsCreated = false;
};