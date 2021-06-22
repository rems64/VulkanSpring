#include <SpringEngine/Graphics/Vulkan/VulkanSurface.hpp>

#include <SpringEngine/Graphics/Vulkan/VulkanApi.hpp>
#include <SpringEngine/Core/Window.hpp>
#include <SpringEngine/Graphics/SwapChain.hpp>

namespace SE
{
	VulkanSurface::VulkanSurface(Window* window) : Surface(window)
	{
		if (glfwCreateWindowSurface(VulkanApi::getInstance(), window->getNative(), nullptr, (VkSurfaceKHR*)&m_surface))
		{
			SE_CORE_ERROR("Failed to create Window surface");
			throw std::runtime_error("Failed to create Window surface");
		}
		SE_CORE_TRACE("Created window surface");
		m_swapchain = SwapChain::build(this);
	}

	VulkanSurface::~VulkanSurface()
	{
		m_swapchain.~shared_ptr();
		vkDestroySurfaceKHR(VulkanApi::getInstance(), (VkSurfaceKHR)m_surface, nullptr);
	}
}