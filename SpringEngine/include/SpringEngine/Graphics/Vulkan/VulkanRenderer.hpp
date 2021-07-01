#pragma once

#include <SpringEngine/Graphics/Renderer.hpp>
#include <SpringEngine/Graphics/Vulkan/VulkanApi.hpp>
#include <SpringEngine/Graphics/Vulkan/VulkanDevice.hpp>

namespace SE
{
	class SE_API VulkanRenderer : public Renderer
	{
	public:
		VulkanRenderer(RendererSpecifications specs);
		~VulkanRenderer();

		virtual int init() override;
	private:
		Shared<VulkanApi> m_renderingApi;
		Shared<VulkanDevice> m_defaultDevice;
	};
}