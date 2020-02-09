#include <Window/Window.h>
#include <Debuging/Assert.h>
#include <TypeDefs/TypeDefs.h>
#include <Instance/Instance.h>
EngWindow::EngWindow()
	: m_Window(nullptr)
{
	m_Resolution.SetResolution(800, 600);
}
void EngWindow::InitWindow(void* engine)
{
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	
	m_Window = glfwCreateWindow(m_Resolution.GetWidth(), m_Resolution.GetHeight(), "Vulkan", nullptr, nullptr);
	glfwSetWindowUserPointer(m_Window, engine);
	glfwSetFramebufferSizeCallback(m_Window, OnFrameBufferResizeCallback);
}

int EngWindow::GetShouldClose()
{
	ENG_ASSERT(m_Window);
	return glfwWindowShouldClose(m_Window);
}

GLFWwindow* EngWindow::GetWindow() const
{
	ENG_ASSERT(m_Window, "Trying to GetWindow before window is initialized");
	return m_Window;
}

const WindowResolution& EngWindow::GetResolution() const
{
	return m_Resolution;
}

void EngWindow::Release()
{
	ENG_ASSERT(m_Window);
	glfwDestroyWindow(m_Window);
}

void EngWindow::OnFrameBufferResizeCallback(GLFWwindow* Window, int Width, int Height)
{
	CInstance* instance = reinterpret_cast<CInstance*>(glfwGetWindowUserPointer(Window));
	instance->RecreateSwapChainOnNextDrawCall();
}
