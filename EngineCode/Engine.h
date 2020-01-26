#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <TypeDefs/TypeDefs.h>
#include <Window/Window.h>
#include <Instance/Instance.h>
class Engine
{
public:
	Engine() = default;
	~Engine() = default;
	void Run();
private:
	void InitVulkan();
	void MainLoop();
	void CleanUp();
private:
	Window m_window;
	Instance m_Instance;

};