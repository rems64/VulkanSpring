#include <SpringEngine/Graphics/Vulkan/VulkanRenderer.hpp>

#include <SpringEngine/Graphics/Vulkan/Device.hpp>
#include <SpringEngine/Graphics/Pipeline.hpp>


namespace SE
{
	std::shared_ptr<Device> VulkanRenderer::m_device;

	VulkanRenderer::VulkanRenderer() : Renderer()
	{
		m_device = std::shared_ptr<Device>(new Device({ .discreteGpu = true, .computeShader = true, .swapChainSupport = true }));
		m_pipeline = Pipeline::build();
	}

	VulkanRenderer::~VulkanRenderer()
	{
		m_pipeline.~shared_ptr();
		m_device.~shared_ptr();
	}
}