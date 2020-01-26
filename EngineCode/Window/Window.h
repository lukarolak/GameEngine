#pragma once
#include <GLFW/glfw3.h>
#include <Window/Resolution.h>
#include <TypeDefs/TypeDefs.h>
class EngWindow
{
public:
	EngWindow();

	void InitWindow();
	int GetShouldClose();
	GLFWwindow* GetWindow() const;
	const WindowResolution& GetResolution() const;
	void Release();
private:
	GLFWwindow* m_Window;
	WindowResolution m_Resolution;
};