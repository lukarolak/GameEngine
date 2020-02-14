#include <Instance/Instance.h>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <Debuging/Validation.h>
#include <Debuging/Assert.h>

VkInstance CInstance::GetInstance() const
{
    return m_Instance;
}

void CInstance::CreateInstance(const EngWindow& Window)
{
    ENG_ASSERT(m_Validation.GetValidationLayersEnabled() && m_Validation.CheckValidationLayerSupport(), "validation layers requested, but not available!");

    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto extensions = m_Validation.GetRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
    if (m_Validation.GetValidationLayersEnabled())
    {
        const std::vector<const char*>& validationLayers = m_Validation.GetValidationLayers();
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();

        m_Validation.populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    }
    else 
    {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    }

    VkResult result;
    result = vkCreateInstance(&createInfo, nullptr, &m_Instance);
    ENG_ASSERT(result == VK_SUCCESS, "failed to create instance!");

    m_Validation.SetupDebugMessenger(m_Instance);
    m_surface.CreateSurface(Window.GetWindow(), m_Instance);
    m_PhysicalDevice.PickPhysicalDevice(m_Instance, m_surface.GetSurface());
    CreateSwapChainParams swapChainParams(m_PhysicalDevice, m_PhysicalDevice.GetQueueFamilyIndices(), m_surface.GetSurface(), Window.GetWindow(), m_Validation);
    m_SwapChain.CreateSwapChain(swapChainParams);
}

void CInstance::Release()
{
    m_SwapChain.Release();
    m_Validation.Release(m_Instance);
    m_surface.Release(m_Instance);
    vkDestroyInstance(m_Instance, nullptr);
}

const CSwapChain& CInstance::GetSwapChain() const
{
    return m_SwapChain;
}

const CPhysicalDevice& CInstance::GetPhysicalDevice() const
{
    return m_PhysicalDevice;
}

void CInstance::DrawFrame(const EngWindow& Window)
{
    CreateSwapChainParams swapChainParams(m_PhysicalDevice, m_PhysicalDevice.GetQueueFamilyIndices(), m_surface.GetSurface(), Window.GetWindow(), m_Validation);
    m_SwapChain.DrawFrame(swapChainParams);
}

void CInstance::RecreateSwapChainOnNextDrawCall()
{
    m_SwapChain.RecreateSwapChainOnNextDrawCall();
}
