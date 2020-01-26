#include "WindowSurface.h"
#include <stdexcept>
void WindowSurface::CreateSurface(GLFWwindow* Window, const VkInstance& Instance)
{
    if (glfwCreateWindowSurface(Instance, Window, nullptr, &m_Surface) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to create window surface!");
    }
}

void WindowSurface::Release(const VkInstance& inInstance)
{
    vkDestroySurfaceKHR(inInstance, m_Surface, nullptr);
}

const VkSurfaceKHR& WindowSurface::GetSurface() const
{
    return m_Surface;
}
