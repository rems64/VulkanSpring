#pragma once

#include <SpringEngine/Graphics/Pipeline.hpp>

namespace SE
{
	class SE_API VulkanPipeline : public Pipeline
	{
	public:
		VulkanPipeline(vk::ShaderModule vertShaderModule, vk::ShaderModule fragShaderModule, vk::PipelineViewportStateCreateInfo* viewportState, vk::RenderPass renderpass);
		~VulkanPipeline();

	private:
		vk::PipelineLayout m_pipelineLayout;
		vk::Pipeline m_graphicsPipeline;
	};
}