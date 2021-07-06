#include <SpringEngine/Graphics/Vulkan/VulkanQueueFamily.hpp>

#include <SpringEngine/Graphics/Vulkan/VulkanPhysicalDevice.hpp>
#include <SpringEngine/Graphics/Vulkan/VulkanSurface.hpp>

namespace SE
{
	VulkanQueueFamily::VulkanQueueFamily(VulkanQueueFamilyRequirements requirements) : m_queueFamily(0), m_properties()
	{
		std::vector<vk::QueueFamilyProperties> queueFamilies = requirements.physicalDevice->getPhysicalDevice()->getQueueFamilyProperties();
		[&]() {
			uint32_t i = -1;
			for (vk::QueueFamilyProperties queueFamily : queueFamilies)
			{
				i++;
				switch (requirements.type)
				{
					case VulkanQueueFamily::Types::Graphics:
					{
						if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics)
						{
							SE_CORE_TRACE("Found graphics queue family");
							m_queueFamily = i;
							return;
						}
					}
					case VulkanQueueFamily::Types::Compute:
					{
						if (queueFamily.queueFlags & vk::QueueFlagBits::eCompute)
						{
							SE_CORE_TRACE("Found compute queue family");
							m_queueFamily = i;
							return;
						}
					}
					case VulkanQueueFamily::Types::Transfer:
					{
						if (queueFamily.queueFlags & vk::QueueFlagBits::eTransfer)
						{
							SE_CORE_TRACE("Found transfer queue family");
							m_queueFamily = i;
							return;
						}
					}
					case VulkanQueueFamily::Types::Presentation:
					{
						if (requirements.physicalDevice->getPhysicalDevice()->getSurfaceSupportKHR(i, *requirements.surface->getSurfaceKHR()))
						{
							SE_CORE_TRACE("Found presentation queue family");
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