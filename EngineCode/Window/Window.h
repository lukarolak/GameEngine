#pragma once
#include <GLFW/glfw3.h>
class Window
{
public:
	Window();

	void InitWindow();

	int GetShouldClose();

	void Release();
private:
	GLFWwindow* m_Window;
};