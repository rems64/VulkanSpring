#include <SpringEngine/Graphics/Vulkan/VulkanViewport.hpp>

#include <SpringEngine/Graphics/SwapChain.hpp>
#include <SpringEngine/Graphics/Vulkan/VulkanSwapChain.hpp>

namespace SE
{
	VulkanViewport::VulkanViewport(SwapChain* swapchain) : Viewport(swapchain)
	{
		m_viewport = vk::Viewport
		{
			.x = 0.0f,
			.y = 0.0f,
			.width = (float)swapchain->getExtent().width,
			.height = (float)swapchain->getExtent().height,
			.minDepth = 0.0f,
			.maxDepth = 1.0f
		};
		m_scissor = vk::Rect2D{ .offset = {0, 0}, .extent = dynamic_cast<VulkanSwapChain*>(swapchain)->getVulkanExtent() };

		 m_viewportState = vk::PipelineViewportStateCreateInfo
		{
			.viewportCount = 1,
			.pViewports = &m_viewport,
			.scissorCount = 1,
			.pScissors = &m_scissor
		};

	}

	VulkanViewport::~VulkanViewport()
	{

	}
}