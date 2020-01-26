#pragma once
#include <vector>
#include <TypeDefs/TypeDefs.h>
#include <vulkan/vulkan_core.h>
class Validation
{
public:
	void SetupDebugMessenger(const VkInstance instance);
	bool CheckValidationLayerSupport();
	bool GetValidationLayersEnabled();
	const std::vector<const char*>& GetValidationLayers();
	std::vector<const char*> GetRequiredExtensions();
	void Release(const VkInstance instance);
	void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
private:
	static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData);
	VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
	void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
private:
	VkDebugUtilsMessengerEXT m_DebugMessenger;
	const std::vector<const char*> m_ValidationLayers{ "VK_LAYER_KHRONOS_validation" };
};