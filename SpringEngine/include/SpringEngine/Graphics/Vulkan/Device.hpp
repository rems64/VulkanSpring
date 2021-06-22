#pragma once
#pragma warning( disable:4251 )

#include <SpringEngine/Graphics/Vulkan/QueueFamily.hpp>

namespace SE
{
	class QueueFamily;
	class VulkanSurface;
	struct SE_API SE_DeviceRequirements
	{
		bool discreteGpu;
		bool computeShader;
		bool swapChainSupport;
	};
	class SE_API Device
	{
	public:
		Device(struct SE_DeviceRequirements requirements);
		Device(const Device& device);
		~Device();

		vk::PhysicalDevice& getPhysicalDevice() { return m_physicalDevice; };
		vk::Device* getDevice() { return &m_device; };

		bool getSurfaceSupport(VulkanSurface* surface, uint32_t index);
		vk::SurfaceCapabilitiesKHR getSurfaceCapabilities(VulkanSurface* surface);
		std::vector<vk::SurfaceFormatKHR> getSurfaceFormats(VulkanSurface* surface);
		std::vector<vk::PresentModeKHR> getPresentModes(VulkanSurface* surface);
		QueueFamily* getQueueFamily(QueueFamily::Types type);
	private:
		vk::PhysicalDevice m_physicalDevice;
		vk::Device m_device;
		std::vector<std::shared_ptr<QueueFamily>> m_queueFamilies;
	};
}