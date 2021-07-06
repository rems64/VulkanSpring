#include <SpringEngine/Graphics/Vulkan/VulkanSurface.hpp>

#include <SpringEngine/Graphics/Vulkan/VulkanApi.hpp>
#include <SpringEngine/Core/Window.hpp>

namespace SE
{
	VulkanSurface::VulkanSurface(SurfaceSpecs requirements) : Surface(requirements), m_surface(makeShared<vk::SurfaceKHR>())
	{
		glfwCreateWindowSurface(*VulkanApi::getInstance(), requirements.window->getNative(), nullptr, reinterpret_cast<VkSurfaceKHR*>(m_surface.get()));
	}

	VulkanSurface::~VulkanSurface()
	{
		VulkanApi::getInstance()->destroySurfaceKHR((VkSurfaceKHR)*m_surface.get());
	}
}