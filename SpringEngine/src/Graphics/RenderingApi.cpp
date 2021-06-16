#include <SpringEngine/Graphics/RenderingApi.hpp>

#include <SpringEngine/Core/Application.hpp>
#include <SpringEngine/Graphics/Vulkan/VulkanApi.hpp>

namespace SE
{
	RenderingApi::Api RenderingApi::m_renderingApi = VulkanApi::Api::SE_VULKAN;
	RenderingApi::RenderingApi()
	{
	}

	RenderingApi::~RenderingApi()
	{
	}

	std::shared_ptr<RenderingApi> RenderingApi::build()
	{
		switch (Application::getRenderingApi())
		{
			case RenderingApi::Api::SE_VULKAN: return std::make_shared<VulkanApi>();
			default: SE_CORE_CRITICAL("No rendering API specified"); return std::make_shared<VulkanApi>();
		}
	}
}