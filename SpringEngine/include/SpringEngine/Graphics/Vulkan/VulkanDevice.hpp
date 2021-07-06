#pragma once

#pragma warning( disable:4251 )
#include <SpringEngine/Graphics/Vulkan/VulkanPhysicalDevice.hpp>

namespace SE
{
	class Surface;
	struct VulkanDeviceRequirements
	{
		Surface* surfaceToUse;
	};
	class SE_API VulkanDevice
	{
	public:
		VulkanDevice(VulkanDeviceRequirements requirements);
		~VulkanDevice();

	private:
		vk::Device m_device;
		Shared<VulkanPhysicalDevice> m_physicalDevice;
	};
}