#pragma once

#include <SpringEngine/Graphics/Vulkan/Device.hpp>

#include <SpringEngine/Graphics/Vulkan/VulkanApi.hpp>
#include <SpringEngine/Graphics/Vulkan/QueueFamily.hpp>

namespace SE
{
	Device::Device(struct SE_DeviceRequirements requirements)
	{
		std::vector<vk::PhysicalDevice> physicalDevices = SE::VulkanApi::getInstance().enumeratePhysicalDevices();
		for (vk::PhysicalDevice physicalDevice : physicalDevices)
		{
			vk::PhysicalDeviceProperties properties = physicalDevice.getProperties();
			if (requirements.discreteGpu)
			{
				if (properties.deviceType != vk::PhysicalDeviceType::eDiscreteGpu)
					continue;
			}
			m_physicalDevice = physicalDevice;
			break;
		}
		if (!m_physicalDevice)
			SE_CORE_CRITICAL("No suitable physical device was found");
		vk::DeviceCreateInfo deviceCreateInfos{};
		std::shared_ptr<QueueFamily> graphicsFamily = std::shared_ptr<QueueFamily>(new QueueFamily(*this, { QueueFamily::Types::Graphics }));
		vk::DeviceQueueCreateInfo queueCreateInfos{ .queueFamilyIndex = graphicsFamily->getQueueFamilyIndex(), .queueCount = 1 };
		deviceCreateInfos.setPQueueCreateInfos(&queueCreateInfos);
		m_device = m_physicalDevice.createDevice(deviceCreateInfos);
	}

	Device::Device(const Device& device) : m_physicalDevice(device.m_physicalDevice), m_device(device.m_device)
	{

	}

	Device::~Device()
	{

	}
}