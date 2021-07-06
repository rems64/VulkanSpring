#pragma once

#pragma warning( disable:4251 )
#include <SpringEngine/Graphics/Vulkan/VulkanQueueFamily.hpp>

namespace SE
{
	class VulkanSurface;
	struct VulkanPhysicalDeviceRequirements
	{
		bool supportComputeShader;
		bool supportGeometryShader;
		bool supportPresentation;
		VulkanSurface* surface;
	};
	class SE_API VulkanPhysicalDevice
	{
	public:
		VulkanPhysicalDevice(VulkanPhysicalDeviceRequirements requirements);
		~VulkanPhysicalDevice();

		void constructQueueFamilies();

		static std::vector<std::pair<int, vk::PhysicalDevice>> getSuitablePhysicalDevices(VulkanPhysicalDeviceRequirements requirements);
		static bool isPhysicalDeviceSuitable(vk::PhysicalDevice physicalDevice, VulkanPhysicalDeviceRequirements requirements);
		inline vk::PhysicalDevice* const getPhysicalDevice() { return &m_physicalDevice; };
		inline VulkanPhysicalDeviceRequirements* getRequirements() { return &m_requirements; };
		VulkanQueueFamily* getQueueFamily(VulkanQueueFamily::Types type);
	private:
		vk::PhysicalDevice m_physicalDevice;
		VulkanPhysicalDeviceRequirements m_requirements;
		std::vector<std::pair<VulkanQueueFamily::Types, Shared<VulkanQueueFamily>>> m_queueFamilies;
	};
}