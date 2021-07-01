#include <SpringEngine/Graphics/Vulkan/VulkanPhysicalDevice.hpp>

#include <SpringEngine/Core/Application.hpp>
#include <SpringEngine/Graphics/Vulkan/VulkanApi.hpp>

namespace SE
{
	VulkanPhysicalDevice::VulkanPhysicalDevice(VulkanPhysicalDeviceRequirements requirements) : m_requirements(requirements)
	{
		std::vector<std::pair<int, vk::PhysicalDevice>> physicalDevices = getSuitablePhysicalDevices(requirements);
		std::sort(physicalDevices.begin(), physicalDevices.end(), [](std::pair<int, vk::PhysicalDevice> a, std::pair<int, vk::PhysicalDevice> b)
			{
				return a.first < b.first;
			});
		for (auto physDevice : physicalDevices)
		{
			SE_VK_DEBUG(SE_CORE_TRACE("Score {} : {}", physDevice.first, physDevice.second.getProperties().deviceName));
		}
	}

	VulkanPhysicalDevice::~VulkanPhysicalDevice()
	{

	}

	std::vector<std::pair<int, vk::PhysicalDevice>> VulkanPhysicalDevice::getSuitablePhysicalDevices(VulkanPhysicalDeviceRequirements requirements)
	{
		SE_VK_DEBUG(SE_CORE_TRACE("Picking device"));
		std::vector<vk::PhysicalDevice> physicalDevices = VulkanApi::getInstance().enumeratePhysicalDevices();
		std::vector<std::pair<int, vk::PhysicalDevice>> scoredPhysicalDevices = {};
		for (vk::PhysicalDevice physDevice : physicalDevices)
		{
			if (!isPhysicalDeviceSuitable(physDevice, requirements))
				continue;
			int score = 0;
			vk::PhysicalDeviceProperties properties = physDevice.getProperties();
			vk::PhysicalDeviceFeatures features = physDevice.getFeatures();
			switch (properties.deviceType)
			{
				case vk::PhysicalDeviceType::eCpu:
					score += 2;
					break;
				case vk::PhysicalDeviceType::eIntegratedGpu:
					score += 10;
					break;
				case vk::PhysicalDeviceType::eDiscreteGpu:
					score += 50;
					break;
			}
			scoredPhysicalDevices.push_back(std::make_pair(score, physDevice));
		}
		if (scoredPhysicalDevices.empty())
			SE_CORE_ERROR("No suitable device were found");

		return scoredPhysicalDevices;
	}

	void VulkanPhysicalDevice::constructQueueFamilies()
	{
		m_queueFamilies.reserve(2);
	}

	bool VulkanPhysicalDevice::isPhysicalDeviceSuitable(vk::PhysicalDevice physicalDevice, VulkanPhysicalDeviceRequirements requirements)
	{
		auto properties = physicalDevice.getProperties();
		auto features = physicalDevice.getFeatures();
		if (requirements.supportGeometryShader)
		{
			if (!features.geometryShader)
			{
				return false;
			}
		}
		if (requirements.supportPresentation)
		{
			//physicalDevice.getSurfaceSupportKHR()
		}
		return true;
	}
}