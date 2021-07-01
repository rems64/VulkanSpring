#include <SpringEngine/Graphics/Vulkan/VulkanQueueFamily.hpp>

#include <SpringEngine/Graphics/Vulkan/VulkanPhysicalDevice.hpp>

namespace SE
{
	VulkanQueueFamily::VulkanQueueFamily(VulkanPhysicalDevice* physicalDevice, VulkanQueueFamily::Types type) : m_queueFamily(0), m_properties()
	{
		std::vector<vk::QueueFamilyProperties> queueFamilies = physicalDevice->getPhysicalDevice()->getQueueFamilyProperties();
		[&]() {
			uint32_t i = -1;
			for (vk::QueueFamilyProperties queueFamily : queueFamilies)
			{
				i++;
				switch (type)
				{
				case VulkanQueueFamily::Types::Graphics:
				{
					if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics)
						m_queueFamily = i;
					return;
				}
				case VulkanQueueFamily::Types::Compute:
				{
					if (queueFamily.queueFlags & vk::QueueFlagBits::eCompute)
					{
						m_queueFamily = i;
						return;
					}
				}
				case VulkanQueueFamily::Types::Transfer:
				{
					if (queueFamily.queueFlags & vk::QueueFlagBits::eTransfer)
					{
						m_queueFamily = i;
						return;
					}
				}
				}
			}
		};
	}

	VulkanQueueFamily::~VulkanQueueFamily()
	{

	}
}