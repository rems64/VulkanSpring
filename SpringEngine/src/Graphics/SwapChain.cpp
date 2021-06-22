#include <SpringEngine/Graphics/SwapChain.hpp>

#include <SpringEngine/Graphics/RenderingApi.hpp>
#include <SpringEngine/Graphics/Vulkan/VulkanSwapChain.hpp>

#include <SpringEngine/Graphics/Vulkan/VulkanSurface.hpp>
#include <SpringEngine/Graphics/Surface.hpp>

namespace SE
{
	SwapChain::SwapChain(Surface* surface)
	{
		
	}

	SwapChain::~SwapChain()
	{

	}

	std::shared_ptr<SwapChain> SwapChain::build(Surface* surface)
	{
		switch (RenderingApi::getApi())
		{
			case RenderingApi::Api::SE_VULKAN:
			{
				return std::make_shared<VulkanSwapChain>(dynamic_cast<VulkanSurface*>(surface));
			}
		}
	}
}