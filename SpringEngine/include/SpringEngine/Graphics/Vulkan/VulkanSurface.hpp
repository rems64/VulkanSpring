#pragma once

#include <SpringEngine/Graphics/Surface.hpp>

namespace SE
{
	class Window;
	class SwapChain;
	class SE_API VulkanSurface : public Surface
	{
	public:
		VulkanSurface(Window* window);
		virtual ~VulkanSurface();

		vk::SurfaceKHR* get() { return &m_surface; };
	private:
		vk::SurfaceKHR m_surface;
		std::shared_ptr<SwapChain> m_swapchain;
	};
}