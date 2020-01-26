#include <Window/Window.h>
#include <Debuging/Assert.h>
#include <TypeDefs/TypeDefs.h>

Window::Window()
	: m_Window(nullptr)
{
}
void Window::InitWindow()
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	
	const engIntU32 WIDTH = 800;
	const engIntU32 HEIGHT = 600;
	
	m_Window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

int Window::GetShouldClose()
{
	ENG_ASSERT(m_Window);
	return glfwWindowShouldClose(m_Window);
}

void Window::Release()
{
	ENG_ASSERT(m_Window);
	glfwDestroyWindow(m_Window);
}
