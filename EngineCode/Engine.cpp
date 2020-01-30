#include "Engine.h"
#include <stdexcept>
void Engine::Run()
{
	m_window.InitWindow();
	InitVulkan();
	MainLoop();
	CleanUp();
}

void Engine::InitVulkan()
{
	m_Instance.CreateInstance(m_window);
	m_CommandBuffer.CreateCommandBuffers(m_Instance);
}

void Engine::MainLoop()
{
	while (m_window.GetShouldClose() == false)
	{
		glfwPollEvents();
		DrawFrame();
	}

	vkDeviceWaitIdle(m_Instance.GetLogicalDevice().GetLogicalDevice());
}

void Engine::CleanUp()
{
	m_Instance.Release();
	m_window.Release();
	glfwTerminate();
}

void Engine::DrawFrame()
{
	const CLogicalDevice& logicalDevice = m_Instance.GetLogicalDevice();
	const CSynchronizationObjectsGroup& synchronizationObjectGroup = logicalDevice.GetSynchronizationObjectsGroup();
	const CSynchronizationObjects& synchronizationObjectsForThisFrame = synchronizationObjectGroup.GetSynchronizationObjectGroup()[m_CurrentFrame];

	vkWaitForFences(logicalDevice.GetLogicalDevice(), 1, &synchronizationObjectsForThisFrame.GetInFlightFence(), VK_TRUE, UINT64_MAX);

	uint32_t imageIndex;
	vkAcquireNextImageKHR(
		logicalDevice.GetLogicalDevice(),
		m_Instance.GetSwapChain().GetSwapChain(),
		UINT64_MAX,
		synchronizationObjectsForThisFrame.GetImageAvailableSemaphore(),
		VK_NULL_HANDLE, 
		&imageIndex);

	// Check if a previous frame is using this image (i.e. there is its fence to wait on)
	if (synchronizationObjectsForThisFrame.GetImageInFlightFence() != VK_NULL_HANDLE) 
	{
		vkWaitForFences(logicalDevice.GetLogicalDevice(), 1, &synchronizationObjectsForThisFrame.GetImageInFlightFence(), VK_TRUE, UINT64_MAX);
	}
	// Mark the image as now being in use by this frame
	m_Instance.SetImageInUse(m_CurrentFrame);

	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

	VkSemaphore waitSemaphores[] = { synchronizationObjectsForThisFrame.GetImageAvailableSemaphore() };
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &m_CommandBuffer.GetCommandBuffers()[imageIndex];

	VkSemaphore signalSemaphores[] = { synchronizationObjectsForThisFrame.GetRenderFinishedSemaphore() };
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = signalSemaphores;

	vkResetFences(logicalDevice.GetLogicalDevice(), 1, &synchronizationObjectsForThisFrame.GetInFlightFence());

	if (vkQueueSubmit(logicalDevice.GetGraphicsQueue(), 1, &submitInfo, synchronizationObjectsForThisFrame.GetInFlightFence()) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to submit draw command buffer!");
	}

	VkSubpassDependency dependency = {};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.srcAccessMask = 0;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = signalSemaphores;

	VkSwapchainKHR swapChains[] = { m_Instance.GetSwapChain().GetSwapChain() };
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapChains;
	presentInfo.pImageIndices = &imageIndex;
	presentInfo.pResults = nullptr; // Optional

	vkQueuePresentKHR(logicalDevice.GetPresentQueue(), &presentInfo);

	m_CurrentFrame = (m_CurrentFrame + 1) % synchronizationObjectGroup.GetMaxFramesInFlight();
}
