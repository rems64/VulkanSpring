#pragma once

namespace SE
{
	class VulkanPhysicalDevice;
	class SE_API VulkanQueueFamily
	{
	public:
		enum class Types
		{
			Graphics = 0,
			Compute = 1,
			Transfer = 2
		};
	public:
		VulkanQueueFamily(VulkanPhysicalDevice* physicalDevice, VulkanQueueFamily::Types types);
		~VulkanQueueFamily();
	private:
		uint32_t m_queueFamily;
		VulkanQueueFamily::Types m_type;
		vk::QueueFamilyProperties m_properties;
	};
}