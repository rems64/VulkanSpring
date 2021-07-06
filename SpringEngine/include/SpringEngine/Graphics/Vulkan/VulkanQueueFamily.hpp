#pragma once

namespace SE
{
	class VulkanPhysicalDevice;
	class VulkanSurface;
	class SE_API VulkanQueueFamily
	{
	public:
		enum class Types
		{
			Graphics     = 1 << 0,
			Compute      = 1 << 1,
			Transfer     = 1 << 2,
			Presentation = 1 << 3
		};

		struct VulkanQueueFamilyRequirements
		{
			VulkanPhysicalDevice* physicalDevice;
			VulkanQueueFamily::Types type;
			VulkanSurface* surface;
		};

	public:
		VulkanQueueFamily(VulkanQueueFamilyRequirements requirements);
		~VulkanQueueFamily();
	private:
		uint32_t m_queueFamily;
		VulkanQueueFamily::Types m_type;
		vk::QueueFamilyProperties m_properties;
	};
}