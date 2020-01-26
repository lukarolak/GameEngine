#include <Instance/Instance.h>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <Debuging/Validation.h>
VkInstance Instance::GetInstance() const
{
    return m_Instance;
}

void Instance::CreateInstance(const EngWindow& Window)
{
    if (m_Validation.GetValidationLayersEnabled() && m_Validation.CheckValidationLayerSupport() == false)
    {
        throw std::runtime_error("validation layers requested, but not available!");
    }

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

    if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS) 
    {
        throw std::runtime_error("failed to create instance!");
    }

    m_Validation.SetupDebugMessenger(m_Instance);
    m_surface.CreateSurface(Window.GetWindow(), m_Instance);
    m_PhysicalDevice.PickPhysicalDevice(m_Instance, m_surface.GetSurface());
    m_LogicalDevice.CreateLogicalDevice(m_PhysicalDevice, m_Validation);
    CreateSwapChainParams swapChainParams(m_PhysicalDevice, m_surface.GetSurface(), Window.GetResolution(), m_LogicalDevice);
    m_SwapChain.CreateSwapChain(swapChainParams);
    CreateImageViewsParams imageViewsParams(m_SwapChain.GetSwapChainImages(), m_SwapChain.GetSwapChainImageFormat(), m_LogicalDevice.GetLogicalDevice());
    m_ImageViews.CreateImageViews(imageViewsParams);
    m_RenderPass.CreateRenderPass(m_SwapChain.GetSwapChainImageFormat(), m_LogicalDevice.GetLogicalDevice());
    CreateGraphicsPipelineParams graphicalPipelineParams(m_LogicalDevice.GetLogicalDevice(), m_SwapChain.GetSwapChainExtent(), m_RenderPass.GetRenderPass());
    m_GraphicPipeline.CreateGraphicsPipeline(graphicalPipelineParams);
}

void Instance::Release()
{
    m_GraphicPipeline.Release(m_LogicalDevice.GetLogicalDevice());
    m_RenderPass.Release(m_LogicalDevice.GetLogicalDevice());
    m_ImageViews.Release(m_LogicalDevice.GetLogicalDevice());
    m_SwapChain.Release(m_LogicalDevice.GetLogicalDevice());
    m_LogicalDevice.Release();
    m_Validation.Release(m_Instance);
    m_surface.Release(m_Instance);
    vkDestroyInstance(m_Instance, nullptr);
}
