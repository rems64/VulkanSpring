#include <SpringEngine/Graphics/Vulkan/VulkanApi.hpp>

#include <SpringEngine/Core/Application.hpp>

namespace SE
{
	vk::Instance VulkanApi::m_instance = vk::Instance();
	VulkanApi::VulkanApi() : RenderingApi(), m_validationLayers( {"VK_LAYER_KHRONOS_validation"} )
	{
		m_enableValidationLayers = true;
	}

	VulkanApi::~VulkanApi()
	{
		destroy();
	}

	int VulkanApi::init()
	{
		SE_CORE_INFO("Vulkan init");
		setupValidationLayers();
		return 0;
	}

	int VulkanApi::create()
	{
		uint32_t glfwExtensionsCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);

		std::vector<vk::ExtensionProperties> extensions = getAvailableExtensions();
		SE_CORE_INFO("{} vulkan extensions are supported", extensions.size());

		vk::ApplicationInfo applicationInfo{ .pApplicationName = Application::getName(), .applicationVersion = VK_MAKE_VERSION(0, 1, 0), .pEngineName = "Spring Engine", .engineVersion = VK_MAKE_VERSION(0, 1, 0), .apiVersion = VK_API_VERSION_1_1 };
		vk::InstanceCreateInfo instanceCreateInfo{ .pApplicationInfo = &applicationInfo, .enabledExtensionCount = glfwExtensionsCount, .ppEnabledExtensionNames = glfwExtensions };
		
		// Validation layers
		if (m_enableValidationLayers) {
			instanceCreateInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayers.size());
			instanceCreateInfo.ppEnabledLayerNames = m_validationLayers.data();
		}
		else {
			instanceCreateInfo.enabledLayerCount = 0;
		}

		m_instance = vk::createInstance(instanceCreateInfo);
		if (m_instance == VK_NULL_HANDLE)
		{
			SE_CORE_CRITICAL("Failed to create Vulkan instance");
		}
		return 0;
	}

	int VulkanApi::destroy()
	{
		SE_CORE_INFO("Destroying api");
		m_instance.destroy();
		return 0;
	}

	void VulkanApi::setupValidationLayers()
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : m_validationLayers) {
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers) {
				if (strcmp(layerName, layerProperties.layerName) == 0) {
					layerFound = true;
					break;
				}
			}
			if (!layerFound)
			{
				SE_CORE_ERROR("Validation layer {} isn't available", layerName);
			}
		}
	}

	std::vector<vk::ExtensionProperties> VulkanApi::getAvailableExtensions()
	{
		return vk::enumerateInstanceExtensionProperties();
	}
}