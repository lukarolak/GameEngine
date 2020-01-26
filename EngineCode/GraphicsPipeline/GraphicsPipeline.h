#pragma once
#include <GraphicsPipeline/CreateGraphicsPipelineParams.h>
#include <vector>
class GraphicsPipeline
{
public:
	void CreateGraphicsPipeline(const CreateGraphicsPipelineParams& Params);
	void Release(const VkDevice& LogicalDevice);
private:
	VkShaderModule CreateShaderModule(const std::vector<char>& code, const VkDevice& LogicalDevice);
	VkPipelineLayout m_PipelineLayout;
	VkPipeline m_GraphicsPipeline;
};