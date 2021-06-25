#include <SpringEngine/Graphics/Renderer.hpp>

#include <SpringEngine/Graphics/RenderingApi.hpp>
#include <SpringEngine/Graphics/Vulkan/VulkanRenderer.hpp>
#include <SpringEngine/Graphics/Pipeline.hpp>

namespace SE
{
	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
	}

	std::shared_ptr<Renderer> Renderer::build()
	{
		switch (RenderingApi::getApi())
		{
			case RenderingApi::Api::SE_VULKAN:
			{
				return std::make_shared<VulkanRenderer>();
			}
			default:
			{
				return std::make_shared<Renderer>();
			}
		}
	}
}