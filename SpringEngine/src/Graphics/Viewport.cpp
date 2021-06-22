#include <SpringEngine/Graphics/Viewport.hpp>

#include <SpringEngine/Graphics/RenderingApi.hpp>
#include <SpringEngine/Graphics/Vulkan/VulkanViewport.hpp>

namespace SE
{
	Viewport::Viewport()
	{

	}

	Viewport::~Viewport()
	{

	}

	std::shared_ptr<Viewport> build()
	{
		switch (RenderingApi::getApi())
		{
			case RenderingApi::Api::SE_VULKAN:
			{
				return std::make_shared<VulkanViewport>();
			}
		}
	}
}