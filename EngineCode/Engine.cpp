#include "Engine.h"
#include <stdexcept>
void CEngine::Run()
{
	m_window.InitWindow(&m_Instance);
	InitVulkan();
	MainLoop();
	CleanUp();
}

void CEngine::InitVulkan()
{
	m_Instance.CreateInstance(m_window);
}

void CEngine::MainLoop()
{
	while (m_window.GetShouldClose() == false)
	{
		glfwPollEvents();
		DrawFrame();
	}
}

void CEngine::CleanUp()
{
	m_Instance.Release();
	m_window.Release();
	glfwTerminate();
}

void CEngine::DrawFrame()
{
	m_Instance.DrawFrame(m_window);
}
