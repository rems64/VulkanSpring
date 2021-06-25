#pragma once

#include <SpringEngine/Graphics/SwapChain.hpp>

namespace SE
{
	class VulkanSurface;
	class SE_API VulkanSwapChain : public SwapChain
	{
	public:
		VulkanSwapChain(VulkanSurface* surface);
		virtual ~VulkanSwapChain();

		vk::SwapchainKHR* getSwapchainKHR() { return m_swapChain.get(); };

		vk::Extent2D getVulkanExtent() { return vk::Extent2D{ .width = m_extent.width, .height = m_extent.height }; };
	private:
		std::shared_ptr<vk::SwapchainKHR> m_swapChain;
		std::vector<vk::Image> m_swapChainImages;
		std::vector<vk::ImageView> m_swapChainImageViews;
		vk::RenderPass m_renderPass;
	};
}