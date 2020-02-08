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
}

void Engine::MainLoop()
{
	while (m_window.GetShouldClose() == false)
	{
		glfwPollEvents();
		DrawFrame();
	}
}

void Engine::CleanUp()
{
	m_Instance.Release();
	m_window.Release();
	glfwTerminate();
}

void Engine::DrawFrame()
{
	m_Instance.DrawFrame();
}
