#pragma once

namespace SE
{
	class SE_API Pipeline
	{
	public:
		Pipeline(vk::ShaderModule vertShaderModule, vk::ShaderModule fragShaderModule);
		~Pipeline();

		static std::shared_ptr<Pipeline> build(vk::ShaderModule vertShaderModule, vk::ShaderModule fragShaderModule);
	};
}