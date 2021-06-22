#include <SpringEngine/Graphics/Vulkan/VulkanViewport.hpp>

namespace SE
{
	VulkanViewport::VulkanViewport() : Viewport()
	{
		//vk::Rect2D scissor{ .offset = {0, 0}, .extent =  };
	}

	VulkanViewport::~VulkanViewport()
	{

	}
}