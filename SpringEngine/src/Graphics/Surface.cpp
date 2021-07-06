#include <SpringEngine/Graphics/Surface.hpp>

#include <SpringEngine/Core/Application.hpp>
#include <SpringEngine/Graphics/Renderer.hpp>
#include <SpringEngine/Graphics/Vulkan/VulkanSurface.hpp>

namespace SE
{
	Surface::Surface(SurfaceSpecs requirements)
	{

	}

	Surface::~Surface()
	{

	}

	Shared<Surface> Surface::build(SurfaceSpecs requirements)
	{
		switch (requirements.renderingApi)
		{
			case RenderingApi::Api::Vulkan:
			{
				SE_CORE_TRACE("Vulkan surface");
				return makeShared<VulkanSurface>(requirements);
			}
			default:
			{
				throw std::runtime_error("No api is not yet supported");
			}
		}
	}
}