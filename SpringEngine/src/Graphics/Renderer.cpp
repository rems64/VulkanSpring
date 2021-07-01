#include <SpringEngine/Graphics/Renderer.hpp>

#include <SpringEngine/Graphics/OpenGL/OpenGLRenderer.hpp>
#include <SpringEngine/Graphics/Vulkan/VulkanRenderer2D.hpp>
#include <SpringEngine/Core/Window.hpp>

namespace SE
{
	Renderer::Renderer(RendererSpecifications specs) : m_specs(specs)
	{
	}

	Renderer::~Renderer()
	{
	}

	std::shared_ptr<Renderer> Renderer::build(RendererSpecifications specs)
	{
		
		switch (specs.api)
		{
			case RenderingApi::Api::None:
			{
				SE_CORE_ERROR("Rendering without an API isn't supported yet");
				throw std::runtime_error("Rendering without an API isn't supported yet");
			}
			case RenderingApi::Api::Vulkan:
			{
				switch (specs.type)
				{
					case Renderer::Types::Renderer2D:
					{
						SE_CORE_INFO("Initialising Vulkan renderer 2D");
						return makeShared<VulkanRenderer2D>(specs);
					}
				}
			}
			case RenderingApi::Api::OpenGL:
			{
				SE_CORE_INFO("Initialasing OpenGL renderer");
				return makeShared<OpenGLRenderer>(specs);
			}
			default:
				throw std::runtime_error("Rendering without an API isn't supported yet");
		}
	}
}