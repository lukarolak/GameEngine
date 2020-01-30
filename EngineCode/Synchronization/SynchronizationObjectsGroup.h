#pragma once
#include <vector>
#include <vulkan/vulkan_core.h>
#include <TypeDefs/TypeDefs.h>
#include <Synchronization/SynchronizationObjects.h>
class CSynchronizationObjectsGroup
{
public:
	void CreateSynchronizationObjectsGroup(const VkDevice& Device);
	void Release(const VkDevice& Device);
	const std::vector<CSynchronizationObjects>& GetSynchronizationObjectGroup() const;
	const engIntU32 GetMaxFramesInFlight() const;
	void SetImageInUse(const engIntU32 FrameIndex);
private:
	std::vector<CSynchronizationObjects> m_SynchronizationObjectGroup;
};