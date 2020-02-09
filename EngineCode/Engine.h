#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <TypeDefs/TypeDefs.h>
#include <Window/Window.h>
#include <Instance/Instance.h>
class CEngine
{
public:
	CEngine() = default;
	~CEngine() = default;
	void Run();
private:
	void InitVulkan();
	void MainLoop();
	void CleanUp();
	void DrawFrame();
private:
	EngWindow m_window;
	CInstance m_Instance;
};