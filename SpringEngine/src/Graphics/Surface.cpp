#include <SpringEngine/Graphics/Surface.hpp>

#include <SpringEngine/Graphics/RenderingApi.hpp>
#include <SpringEngine/Graphics/Vulkan/VulkanSurface.hpp>
#include <SpringEngine/Core/Window.hpp>

namespace SE
{
	Surface::Surface(Window* window) : m_linkedWindow(window)
	{

	}

	Surface::~Surface()
	{

	}

	std::shared_ptr<Surface> Surface::build(Window* window)
	{
		switch (RenderingApi::getApi())
		{
			case RenderingApi::Api::SE_VULKAN:
			{
				return std::make_shared<VulkanSurface>(window);
			}
		}
	}
}