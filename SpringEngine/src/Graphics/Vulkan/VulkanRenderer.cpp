#include <SpringEngine/Graphics/Vulkan/VulkanRenderer.hpp>

#include <SpringEngine/Graphics/Vulkan/Device.hpp>

namespace SE
{
	std::shared_ptr<Device> VulkanRenderer::m_device;

	VulkanRenderer::VulkanRenderer()
	{
		m_device = std::shared_ptr<Device>(new Device({ .discreteGpu = true, .computeShader = true, .swapChainSupport = true }));
	}

	VulkanRenderer::~VulkanRenderer()
	{
		m_device.~shared_ptr();
	}
}