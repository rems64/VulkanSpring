#pragma once
#include <SpringEngine/Graphics/Vulkan/VulkanRenderer.hpp>

namespace SE
{
	VulkanRenderer::VulkanRenderer(RendererSpecifications specs) : Renderer(specs)
	{
		if (m_specs.api != RenderingApi::Api::Vulkan)
			SE_CORE_ERROR("An error occured while initialising renderer");
		if (m_specs.mode != Renderer::Modes::OnScreen)
			SE_CORE_ERROR("Offscreen rendering is not yet supported");
		switch (m_specs.mode)
		{
			case Renderer::Modes::OnScreen:
			{
				break;
			}
			default:
				throw std::runtime_error("Offscreen rendering is not yet supported");
		}

	}

	VulkanRenderer::~VulkanRenderer()
	{
		m_renderingApi->destroy();
	}

	int VulkanRenderer::coreInit()
	{
		SE_VK_DEBUG(SE_CORE_TRACE("VulkanRenderer core init"));
		m_renderingApi = makeShared<VulkanApi>();
		m_renderingApi->init();
		return 0;
	}

	int VulkanRenderer::init()
	{
		SE_VK_DEBUG(SE_CORE_TRACE("VulkanRenderer init"));
		m_defaultDevice = makeShared<VulkanDevice>( VulkanDeviceRequirements{ .surfaceToUse = m_specs.surface } );
		return 0;
	}
}