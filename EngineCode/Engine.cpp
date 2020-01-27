#include "Engine.h"

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
	}
}

void Engine::CleanUp()
{
	m_Instance.Release();
	m_window.Release();
	glfwTerminate();
}
