#include <SpringEngine/Graphics/Vulkan/VulkanDevice.hpp>

namespace SE
{
	VulkanDevice::VulkanDevice()
	{
		VulkanPhysicalDeviceRequirements requirements
		{
			.supportComputeShader = true
		};
		m_physicalDevice = makeShared<VulkanPhysicalDevice>(requirements);
	}

	VulkanDevice::~VulkanDevice()
	{

	}
}