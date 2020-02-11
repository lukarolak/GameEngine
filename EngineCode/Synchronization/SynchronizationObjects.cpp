#include <Synchronization/SynchronizationObjectsGroup.h>
#include <Debuging/Assert.h>
constexpr engIntU32 m_MaxFramesInFlight = 2;

void CSynchronizationObjectsGroup::CreateSynchronizationObjectsGroup(const VkDevice& Device)
{
	m_SynchronizationObjectGroup.resize(m_MaxFramesInFlight);

	for (CSynchronizationObjects& group : m_SynchronizationObjectGroup)
	{
		group.CreateSynchronnizationObjects(Device);
	}
}

void CSynchronizationObjectsGroup::Release(const VkDevice& Device)
{
	for (CSynchronizationObjects& group : m_SynchronizationObjectGroup)
	{
		group.Release(Device);
	}
}

const std::vector<CSynchronizationObjects>& CSynchronizationObjectsGroup::GetSynchronizationObjectGroup() const
{
	return m_SynchronizationObjectGroup;
}

const engIntU32 CSynchronizationObjectsGroup::GetMaxFramesInFlight() const
{
	return m_MaxFramesInFlight;
}

void CSynchronizationObjectsGroup::SetImageInUse(const engIntU32 FrameIndex)
{
	ENG_ASSERT(FrameIndex <= m_SynchronizationObjectGroup.size(), "Frame index out of bounds");
	m_SynchronizationObjectGroup[FrameIndex].SetImageInUse();
}
