#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <Debuging/Validation.h>
class Instance
{
public:
	void CreateInstance();
	void Release();
private:
	VkInstance m_Instance;
	Validation m_Validation;
};