#pragma once
#include <Buffers/Buffer.h>
class CStagingBuffer : public CBuffer 
{
public:
	void CreateStagingBuffer(std::vector<CVertex>& Data, const VkDevice& LogicalDevice, const CPhysicalDevice& PhysicalDevice);
	void Release(const VkDevice& Device);
private:

};