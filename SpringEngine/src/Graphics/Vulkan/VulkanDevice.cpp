#include <SpringEngine/Graphics/Vulkan/VulkanDevice.hpp>

#include <SpringEngine/Graphics/Surface.hpp>
#include <SpringEngine/Graphics/Vulkan/VulkanSurface.hpp>

namespace SE
{
	VulkanDevice::VulkanDevice(VulkanDeviceRequirements requirements)
	{
		SE_PROFILE_SCOPE("Vulkan device creation");
		VulkanPhysicalDeviceRequirements physicalDeviceRequirements
		{
			.supportComputeShader = true,
			.surface = dynamic_cast<VulkanSurface*>(requirements.surfaceToUse)
		};
		m_physicalDevice = makeShared<VulkanPhysicalDevice>(physicalDeviceRequirements);
	}

	VulkanDevice::~VulkanDevice()
	{

	}
}