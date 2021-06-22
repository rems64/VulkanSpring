#pragma once

#include <SpringEngine/Graphics/Viewport.hpp>

namespace SE
{
	class SE_API VulkanViewport : public Viewport
	{
	public:
		VulkanViewport();
		~VulkanViewport();
	private:
		vk::Viewport m_viewport;
	};
}