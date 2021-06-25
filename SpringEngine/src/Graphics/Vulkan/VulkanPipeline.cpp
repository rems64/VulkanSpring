#include <SpringEngine/Graphics/Vulkan/VulkanPipeline.hpp>

#include <SpringEngine/Graphics/Vulkan/VulkanRenderer.hpp>
#include <SpringEngine/Graphics/Vulkan/Device.hpp>


namespace SE
{
	VulkanPipeline::VulkanPipeline(vk::ShaderModule vertShaderModule, vk::ShaderModule fragShaderModule, vk::PipelineViewportStateCreateInfo* viewportState, vk::RenderPass renderpass) : Pipeline(vertShaderModule, fragShaderModule)
	{
		vk::PipelineVertexInputStateCreateInfo vertexInputInfo{ .vertexBindingDescriptionCount = 0, .pVertexBindingDescriptions = nullptr, .vertexAttributeDescriptionCount = 0, .pVertexAttributeDescriptions = nullptr };

		vk::PipelineInputAssemblyStateCreateInfo inputAssembly{ .topology = vk::PrimitiveTopology::eTriangleList, .primitiveRestartEnable = false };

		vk::PipelineShaderStageCreateInfo vertShaderStageInfo{ .stage = vk::ShaderStageFlagBits::eVertex, .module = vertShaderModule, .pName = "main" };
		vk::PipelineShaderStageCreateInfo fragShaderStageInfo{ .stage = vk::ShaderStageFlagBits::eFragment, .module = fragShaderModule, .pName = "main" };

		vk::PipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

		vk::PipelineRasterizationStateCreateInfo rasterizer
		{
			.depthClampEnable = false,
			.rasterizerDiscardEnable = false,
			.polygonMode = vk::PolygonMode::eFill,
			.cullMode = vk::CullModeFlagBits::eBack,
			.frontFace = vk::FrontFace::eClockwise,
			.depthBiasEnable = false,
			.depthBiasConstantFactor = 0.0f,
			.depthBiasClamp = 0.0f,
			.depthBiasSlopeFactor = 0.0f,
			.lineWidth = 1.0f
		};

		vk::PipelineMultisampleStateCreateInfo multisampling
		{
			.rasterizationSamples = vk::SampleCountFlagBits::e1,
			.sampleShadingEnable = false,
			.minSampleShading = 1.0f,
			.pSampleMask = nullptr,
			.alphaToCoverageEnable = false,
			.alphaToOneEnable = false
		};

		vk::PipelineColorBlendAttachmentState colorBlendAttachment
		{
			.blendEnable = false,
			.srcColorBlendFactor = vk::BlendFactor::eOne,
			.dstColorBlendFactor = vk::BlendFactor::eZero,
			.colorBlendOp = vk::BlendOp::eAdd,
			.srcAlphaBlendFactor = vk::BlendFactor::eOne,
			.dstAlphaBlendFactor = vk::BlendFactor::eZero,
			.alphaBlendOp = vk::BlendOp::eAdd,
			.colorWriteMask = vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA
		};

		vk::PipelineColorBlendStateCreateInfo colorBlending
		{
			.logicOpEnable = false,
			.logicOp = vk::LogicOp::eCopy,
			.attachmentCount = 1,
			.pAttachments = &colorBlendAttachment
		};

		vk::DynamicState dynamicStates[] = {
			vk::DynamicState::eViewport,
			vk::DynamicState::eLineWidth
		};

		vk::PipelineDynamicStateCreateInfo dynamicState
		{
			.dynamicStateCount = 2,
			.pDynamicStates = dynamicStates
		};

		vk::PipelineLayoutCreateInfo pipelineLayoutCreateInfo
		{
			.setLayoutCount = 0,
			.pSetLayouts = nullptr,
			.pushConstantRangeCount = 0,
			.pPushConstantRanges = nullptr
		};
		m_pipelineLayout = VulkanRenderer::getDevice()->getDevice()->createPipelineLayout(pipelineLayoutCreateInfo);
		vk::GraphicsPipelineCreateInfo pipelineInfo
		{
			.stageCount = 2,
			.pStages = shaderStages,
			.pVertexInputState = &vertexInputInfo,
			.pInputAssemblyState = &inputAssembly,
			.pViewportState = viewportState,
			.pRasterizationState = &rasterizer,
			.pMultisampleState = &multisampling,
			.pDepthStencilState = nullptr,
			.pColorBlendState = &colorBlending,
			.pDynamicState = nullptr,
			.layout = m_pipelineLayout,
			.renderPass = renderpass,
			.subpass = 0,
			.basePipelineHandle = nullptr,
			.basePipelineIndex = -1
		};
		m_graphicsPipeline = VulkanRenderer::getDevice()->getDevice()->createGraphicsPipeline(nullptr, pipelineInfo).value;
	}

	VulkanPipeline::~VulkanPipeline()
	{
		VulkanRenderer::getDevice()->getDevice()->destroyPipeline(m_graphicsPipeline);
		VulkanRenderer::getDevice()->getDevice()->destroyPipelineLayout(m_pipelineLayout);
	}
}