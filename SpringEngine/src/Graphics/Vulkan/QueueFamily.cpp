#include <SpringEngine/Graphics/Vulkan/QueueFamily.hpp>

#include <SpringEngine/Graphics/Vulkan/Device.hpp>

namespace SE
{
	QueueFamily::QueueFamily(Device device, QueueFamilyRequirements requirements)
	{
		SE_CORE_TRACE("Queue family pop");
		std::vector<vk::QueueFamilyProperties> queueFamilies = device.getPhysicalDevice().getQueueFamilyProperties();
		uint32_t i = 0;
		[&]
		{
			for (vk::QueueFamilyProperties queueFamily : queueFamilies)
			{
				i++;
				switch (requirements.type)
				{
				case QueueFamily::Types::Graphics:
				{
					if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics)
					{
						m_queueFamilyIndex = i - 1;
						SE_CORE_TRACE("Graphics queue family found");
						return;
					}
				}
				case QueueFamily::Types::Compute:
				{
					if (queueFamily.queueFlags & vk::QueueFlagBits::eCompute)
					{
						SE_CORE_TRACE("Compute queue family found");
						m_queueFamilyIndex = i - 1;
						return;
					}
				}
				default:
					break;
				}
			}
		};
	}

	QueueFamily::~QueueFamily()
	{

	}
}