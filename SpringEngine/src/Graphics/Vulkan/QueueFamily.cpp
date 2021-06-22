#include <SpringEngine/Graphics/Vulkan/QueueFamily.hpp>

#include <SpringEngine/Graphics/Vulkan/Device.hpp>

namespace SE
{
	QueueFamily::QueueFamily(Device* device, QueueFamilyRequirements requirements) : m_priority(1.0f), m_device(device), m_type(requirements.type)
	{
		std::vector<vk::QueueFamilyProperties> queueFamilies = device->getPhysicalDevice().getQueueFamilyProperties();
		m_queueFamilyIndex = selectQueue(queueFamilies, requirements);
	}

	QueueFamily::~QueueFamily()
	{

	}

	uint32_t QueueFamily::selectQueue(std::vector<vk::QueueFamilyProperties>& queueFamilies, QueueFamilyRequirements requirements)
	{
		uint32_t i = 0;
		for (vk::QueueFamilyProperties queueFamily : queueFamilies)
		{
			i++;
			switch (requirements.type)
			{
			case QueueFamily::Types::Graphics:
			{
				if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics)
				{
					SE_CORE_TRACE("Graphics queue family found");
					return i - 1;
				}
			}
			case QueueFamily::Types::Compute:
			{
				if (queueFamily.queueFlags & vk::QueueFlagBits::eCompute)
				{
					SE_CORE_TRACE("Compute queue family found");
					return i - 1;
				}
			}
			case QueueFamily::Types::Presentation:
			{
				if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics)
				{
					SE_CORE_TRACE("Presentation queue family found");
					return i - 1;
				}
			}
			default:
				break;
			}
		}
		return 0;
	}
}