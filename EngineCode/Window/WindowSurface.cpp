#include "WindowSurface.h"
#include <stdexcept>
#include <Debuging/Assert.h>
void CWindowSurface::CreateSurface(GLFWwindow* Window, const VkInstance& Instance)
{
    VkResult result;
    result = glfwCreateWindowSurface(Instance, Window, nullptr, &m_Surface);
    ENG_ASSERT(result == VK_SUCCESS, "failed to create window surface!");
}

void CWindowSurface::Release(const VkInstance& inInstance)
{
    vkDestroySurfaceKHR(inInstance, m_Surface, nullptr);
}

const VkSurfaceKHR& CWindowSurface::GetSurface() const
{
    return m_Surface;
}
