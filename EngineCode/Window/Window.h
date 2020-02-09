#pragma once
#include <GLFW/glfw3.h>
#include <Window/Resolution.h>
#include <TypeDefs/TypeDefs.h>
class EngWindow
{
public:
	EngWindow();

	void InitWindow(void* engine);
	int GetShouldClose();
	GLFWwindow* GetWindow() const;
	const WindowResolution& GetResolution() const;
	void Release();
private:
	static void OnFrameBufferResizeCallback(GLFWwindow* Window, int Width, int Height);

private:
	GLFWwindow* m_Window;
	WindowResolution m_Resolution;
};