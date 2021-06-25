#pragma once

#include <SpringEngine/Graphics/Viewport.hpp>

namespace SE
{
	class SwapChain;
	class SE_API VulkanViewport : public Viewport
	{
	public:
		VulkanViewport(SwapChain* swapchain);
		~VulkanViewport();

		vk::PipelineViewportStateCreateInfo getViewportState() { return m_viewportState; };
	private:
		vk::Viewport m_viewport;
		vk::Rect2D m_scissor;
		vk::PipelineViewportStateCreateInfo m_viewportState;
	};
}