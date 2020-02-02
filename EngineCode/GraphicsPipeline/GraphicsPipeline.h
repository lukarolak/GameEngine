#pragma once
#include <GraphicsPipeline/Types/CreateGraphicsPipelineParams.h>
#include <vector>
class CGraphicsPipeline
{
public:
	void CreateGraphicsPipeline(const CreateGraphicsPipelineParams& Params);
	void Release(const VkDevice& LogicalDevice);
	const VkPipeline& GetGraphicsPipeline() const;
private:
	VkShaderModule CreateShaderModule(const std::vector<char>& code, const VkDevice& LogicalDevice);
	VkPipelineLayout m_PipelineLayout;
	VkPipeline m_GraphicsPipeline;
};