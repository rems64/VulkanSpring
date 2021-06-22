#pragma once

namespace SE
{
	class SE_API Shader
	{
	public:
		Shader(const char* vertexShader, const char* fragmentShader);
		~Shader();

		static vk::ShaderModule createShaderModule(const std::vector<char>& code);
	private:
		vk::ShaderModule m_vertShaderModule;
		vk::ShaderModule m_fragShaderModule;
	};
}