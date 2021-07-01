#pragma once

#pragma warning( disable:4251 )
#include <SpringEngine/Graphics/Vulkan/VulkanPhysicalDevice.hpp>

namespace SE
{
	class SE_API VulkanDevice
	{
	public:
		VulkanDevice();
		~VulkanDevice();

	private:
		vk::Device m_device;
		Shared<VulkanPhysicalDevice> m_physicalDevice;
	};
}