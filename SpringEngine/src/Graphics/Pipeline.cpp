#include <SpringEngine/Graphics/Pipeline.hpp>

#include <SpringEngine/Graphics/RenderingApi.hpp>
#include <SpringEngine/Graphics/Vulkan/VulkanPipeline.hpp>

namespace SE
{
	Pipeline::Pipeline(vk::ShaderModule vertShaderModule, vk::ShaderModule fragShaderModule)
	{

	}

	Pipeline::~Pipeline()
	{

	}

	std::shared_ptr<Pipeline> Pipeline::build(vk::ShaderModule vertShaderModule, vk::ShaderModule fragShaderModule)
	{
		switch (RenderingApi::getApi())
		{
			case RenderingApi::Api::SE_VULKAN:
			{
				return std::make_shared<VulkanPipeline>(vertShaderModule, fragShaderModule);
			}
		}
	}
}