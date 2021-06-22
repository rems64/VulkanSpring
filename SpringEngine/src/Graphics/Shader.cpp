#include <SpringEngine/Graphics/Shader.hpp>

#include <SpringEngine/Graphics/Vulkan/VulkanRenderer.hpp>
#include <SpringEngine/Graphics/Vulkan/Device.hpp>

namespace SE
{
	Shader::Shader(const char* vertexShader, const char* fragmentShader)
	{
		size_t fileSize;

		std::ifstream vertexShaderFile(vertexShader, std::ios::ate | std::ios::binary);
		if (!vertexShaderFile.is_open())
			SE_CORE_WARN("Can't open vertex shader ({})", vertexShader);

		fileSize = (size_t)vertexShaderFile.tellg();
		std::vector<char> vertShaderCode(fileSize);
		vertexShaderFile.seekg(0);
		vertexShaderFile.read(vertShaderCode.data(), fileSize);
		vertexShaderFile.close();

		std::ifstream fragmentShaderFile(vertexShader, std::ios::ate | std::ios::binary);
		if (!fragmentShaderFile.is_open())
			SE_CORE_WARN("Can't open vertex shader ({})", fragmentShader);
		fileSize = (size_t)fragmentShaderFile.tellg();
		std::vector<char> fragShaderCode(fileSize);
		fragmentShaderFile.seekg(0);
		fragmentShaderFile.read(fragShaderCode.data(), fileSize);
		fragmentShaderFile.close();

		m_vertShaderModule = createShaderModule(vertShaderCode);
		m_fragShaderModule = createShaderModule(fragShaderCode);

		vk::PipelineShaderStageCreateInfo vertShaderStageInfo{ .stage = vk::ShaderStageFlagBits::eVertex, .module = m_vertShaderModule, .pName = "main" };
		vk::PipelineShaderStageCreateInfo fragShaderStageInfo{ .stage = vk::ShaderStageFlagBits::eFragment, .module = m_fragShaderModule, .pName = "main" };

		vk::PipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

		vk::PipelineVertexInputStateCreateInfo vertexInputInfo{ .vertexBindingDescriptionCount = 0, .pVertexBindingDescriptions = nullptr, .vertexAttributeDescriptionCount = 0, .pVertexAttributeDescriptions = nullptr };

		vk::PipelineInputAssemblyStateCreateInfo inputAssembly{ .topology = vk::PrimitiveTopology::eTriangleList, .primitiveRestartEnable = false };
	}

	Shader::~Shader()
	{
		VulkanRenderer::getDevice()->getDevice()->destroyShaderModule(m_vertShaderModule);
		VulkanRenderer::getDevice()->getDevice()->destroyShaderModule(m_fragShaderModule);
	}

	vk::ShaderModule Shader::createShaderModule(const std::vector<char>& code)
	{
		vk::ShaderModuleCreateInfo createInfo{ .codeSize = code.size(), .pCode = reinterpret_cast<const uint32_t*>(code.data()) };
		 vk::ShaderModule shaderModule = VulkanRenderer::getDevice()->getDevice()->createShaderModule(createInfo);
		 if (!shaderModule)
			 SE_CORE_ERROR("Failed to create shader module");

		 return shaderModule;
	}
}