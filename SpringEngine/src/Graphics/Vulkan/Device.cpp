#pragma once

#include <SpringEngine/Graphics/Vulkan/Device.hpp>

#include <SpringEngine/Graphics/Vulkan/VulkanApi.hpp>
#include <SpringEngine/Graphics/Vulkan/QueueFamily.hpp>
#include <SpringEngine/Graphics/Vulkan/VulkanSurface.hpp>

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

		// Queue families
		vk::DeviceCreateInfo deviceCreateInfos{};
		std::shared_ptr<QueueFamily> graphicsFamily      = std::shared_ptr<QueueFamily>(new QueueFamily(this, { QueueFamily::Types::Graphics      }));
		m_queueFamilies.push_back(graphicsFamily);
		std::shared_ptr<QueueFamily> computeFamily       = std::shared_ptr<QueueFamily>(new QueueFamily(this, { QueueFamily::Types::Compute       }));
		m_queueFamilies.push_back(computeFamily);
		std::shared_ptr<QueueFamily> presentationFamily  = std::shared_ptr<QueueFamily>(new QueueFamily(this, { QueueFamily::Types::Presentation  }));
		m_queueFamilies.push_back(presentationFamily);
		std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> indices;
		queueCreateInfos.push_back({ .queueFamilyIndex = graphicsFamily->getQueueFamilyIndex(), .queueCount = 1, .pQueuePriorities = graphicsFamily->getPriority() });
		indices.insert(graphicsFamily->getQueueFamilyIndex());
		if (!indices.contains(computeFamily->getQueueFamilyIndex()))
		{
			queueCreateInfos.push_back({ .queueFamilyIndex = computeFamily->getQueueFamilyIndex() , .queueCount = 1, .pQueuePriorities = computeFamily->getPriority()  });
			indices.insert(computeFamily->getQueueFamilyIndex());
		}
		if (!indices.contains(presentationFamily->getQueueFamilyIndex()))
		{
			queueCreateInfos.push_back({ .queueFamilyIndex = presentationFamily->getQueueFamilyIndex() , .queueCount = 1, .pQueuePriorities = presentationFamily->getPriority() });
			indices.insert(presentationFamily->getQueueFamilyIndex());
		}
		deviceCreateInfos.setPQueueCreateInfos(queueCreateInfos.data());
		deviceCreateInfos.setQueueCreateInfoCount((uint32_t)queueCreateInfos.size());

		// Extensions
		std::vector<const char*> deviceExtensions;
		if (requirements.swapChainSupport)
		{
			deviceExtensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
		}

		deviceCreateInfos.setEnabledExtensionCount(deviceExtensions.size());
		deviceCreateInfos.setPpEnabledExtensionNames(deviceExtensions.data());
		m_device = m_physicalDevice.createDevice(deviceCreateInfos);
	}

	Device::Device(const Device& device) : m_physicalDevice(device.m_physicalDevice), m_device(device.m_device)
	{

	}

	Device::~Device()
	{
		m_device.destroy();
	}


	bool Device::getSurfaceSupport(VulkanSurface* surface, uint32_t index)
	{
		return m_physicalDevice.getSurfaceSupportKHR(index, *surface->get());
	}

	vk::SurfaceCapabilitiesKHR Device::getSurfaceCapabilities(VulkanSurface* surface)
	{
		return m_physicalDevice.getSurfaceCapabilitiesKHR(*surface->get());
	}

	std::vector<vk::SurfaceFormatKHR> Device::getSurfaceFormats(VulkanSurface* surface)
	{
		return m_physicalDevice.getSurfaceFormatsKHR(*surface->get());
	}

	std::vector<vk::PresentModeKHR> Device::getPresentModes(VulkanSurface* surface)
	{
		return m_physicalDevice.getSurfacePresentModesKHR(*surface->get());
	}

	QueueFamily* Device::getQueueFamily(QueueFamily::Types type)
	{
		for (auto queueFamily : m_queueFamilies)
		{
			if (queueFamily->getType() == type)
			{
				return queueFamily.get();
			}
		}
	}
}