#pragma once

namespace SE
{
	class QueueFamily;
	struct SE_API SE_DeviceRequirements
	{
		bool discreteGpu;
		bool computeShader;
	};
	class SE_API Device
	{
	public:
		Device(struct SE_DeviceRequirements requirements);
		Device(const Device& device);
		~Device();

		vk::PhysicalDevice& getPhysicalDevice() { return m_physicalDevice; };
	private:
		vk::PhysicalDevice m_physicalDevice;
		vk::Device m_device;
		std::vector<std::shared_ptr<QueueFamily>> m_queueFamilies;
	};
}