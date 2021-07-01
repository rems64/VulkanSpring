#pragma once

#include <SpringEngine/Graphics/Vulkan/VulkanRenderer.hpp>

namespace SE
{
	class SE_API VulkanRenderer2D : public VulkanRenderer
	{
	public:
		VulkanRenderer2D(Renderer::RendererSpecifications specs);
		~VulkanRenderer2D();

		virtual int init() override;
	};
}