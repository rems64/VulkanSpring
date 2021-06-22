#pragma once

#include <SpringEngine/Graphics/SwapChain.hpp>

namespace SE
{
	class VulkanSurface;
	class SE_API VulkanSwapChain : public SwapChain
	{
	public:
		VulkanSwapChain(VulkanSurface* surface);
		~VulkanSwapChain();
	private:
		std::shared_ptr<vk::SwapchainKHR> m_swapChain;
		std::vector<vk::Image> m_swapChainImages;
		std::vector<vk::ImageView> m_swapChainImageViews;
	};
}