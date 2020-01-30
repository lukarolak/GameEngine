#include <Devices/Synchronization/SynchronizationObjects.h>
#include <Debuging/Assert.h>
void CSynchronizationObjects::CreateSynchronnizationObjects(const VkDevice& device)
{
	VkSemaphoreCreateInfo semaphoreInfo = {};
	semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	VkFenceCreateInfo fenceInfo = {};
	fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	VkResult cratedImageAvailabeSemaphore = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &m_ImageAvailableSemaphore);
	VkResult cratedRenderFinishedSemaphore = vkCreateSemaphore(device, &semaphoreInfo, nullptr, &m_RenderFinishedSemaphore);
	VkResult createdInFlightFence = vkCreateFence(device, &fenceInfo, nullptr, &m_InFlightFence);

	if (cratedImageAvailabeSemaphore != VK_SUCCESS || cratedRenderFinishedSemaphore != VK_SUCCESS || createdInFlightFence != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create synchronization objects for a frame!");
	}

	m_SynchronizationObjectsCreated = true;
}

const VkSemaphore& CSynchronizationObjects::GetImageAvailableSemaphore() const
{
	ENG_ASSERT(m_SynchronizationObjectsCreated, "Semaphore not created");
	return m_ImageAvailableSemaphore;
}

const VkSemaphore& CSynchronizationObjects::GetRenderFinishedSemaphore() const
{
	ENG_ASSERT(m_SynchronizationObjectsCreated, "Semaphore not created");
	return m_RenderFinishedSemaphore;
}

const VkFence& CSynchronizationObjects::GetInFlightFence() const
{
	return m_InFlightFence;
}

const VkFence& CSynchronizationObjects::GetImageInFlightFence() const
{
	return m_ImageInFlight;
}

void CSynchronizationObjects::SetImageInFlight(const VkFence& fence)
{
	m_ImageInFlight = fence;
}

void CSynchronizationObjects::Release(const VkDevice& device)
{
	vkDestroySemaphore(device, m_RenderFinishedSemaphore, nullptr);
	vkDestroySemaphore(device, m_ImageAvailableSemaphore, nullptr);
	vkDestroyFence(device, m_InFlightFence, nullptr);
}

void CSynchronizationObjects::SetImageInUse()
{
	m_ImageInFlight = m_InFlightFence;
}
