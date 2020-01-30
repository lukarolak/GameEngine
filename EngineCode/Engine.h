#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <TypeDefs/TypeDefs.h>
#include <Window/Window.h>
#include <Instance/Instance.h>
#include <GraphicsPipeline/CommandBuffer.h>
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
	void DrawFrame();
private:
	EngWindow m_window;
	CInstance m_Instance;
	CCommandBuffer m_CommandBuffer;
	engIntU32 m_CurrentFrame = 0;
};