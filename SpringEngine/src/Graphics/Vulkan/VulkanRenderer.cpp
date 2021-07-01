#pragma once
#include <SpringEngine/Graphics/Vulkan/VulkanRenderer.hpp>

namespace SE
{
	VulkanRenderer::VulkanRenderer(RendererSpecifications specs) : Renderer(specs)
	{
		if (m_specs.api != RenderingApi::Api::Vulkan)
			SE_CORE_ERROR("An error occured while initialising renderer");

	}

	VulkanRenderer::~VulkanRenderer()
	{
		m_renderingApi->destroy();
	}

	int VulkanRenderer::init()
	{
		SE_VK_DEBUG(SE_CORE_TRACE("VulkanRenderer init"));
		m_renderingApi = makeShared<VulkanApi>();
		m_renderingApi->init();
		m_defaultDevice = makeShared<VulkanDevice>();
		return 0;
	}
}