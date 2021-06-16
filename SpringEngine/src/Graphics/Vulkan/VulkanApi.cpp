#include <SpringEngine/Graphics/Vulkan/VulkanApi.hpp>

namespace SE
{
	VkInstance VulkanApi::m_instance = nullptr;
	VulkanApi::VulkanApi() : RenderingApi(), m_appInfo(), m_createInfo(), m_validationLayers( {"VK_LAYER_KHRONOS_validation"} )
	{
		m_enableValidationLayers = true;
	}

	VulkanApi::~VulkanApi()
	{
		destroy();
	}

	int VulkanApi::init()
	{
		SE_CORE_WARN("Vulkan init");

		if (m_enableValidationLayers && !checkValidationLayerSupport()) {
			throw std::runtime_error("validation layers requested, but not available!");
		}



		m_appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		m_appInfo.pApplicationName = "Vulkan renderer";
		m_appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		m_appInfo.pEngineName = "No Engine.";
		m_appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		m_appInfo.apiVersion = VK_API_VERSION_1_0;

		
		m_createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		m_createInfo.pApplicationInfo = &m_appInfo;

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		m_createInfo.enabledExtensionCount = glfwExtensionCount;
		m_createInfo.ppEnabledExtensionNames = glfwExtensions;
		if (m_enableValidationLayers) {
			m_createInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayers.size());
			m_createInfo.ppEnabledLayerNames = m_validationLayers.data();
		}
		else {
			m_createInfo.enabledLayerCount = 0;
		}
		return 0;
	}

	int VulkanApi::create()
	{
		VkResult result = vkCreateInstance(&m_createInfo, nullptr, &m_instance);
		if (result != VK_SUCCESS)
		{
			SE_CORE_ERROR("Failed to create Vulkan instance");
			throw;
		}

		uint32_t extensionCount = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
		SE_CORE_TRACE("Available extensions:");

		for (const auto& extension : extensions) {
			SE_CORE_TRACE("\t {}", extension.extensionName);
		}
		selectPhysicalDevice();
		createDevice({ VK_KHR_SWAPCHAIN_EXTENSION_NAME });
		return 0;
	}

	int VulkanApi::destroy()
	{
		SE_CORE_WARN("Destroying api");
		vkDestroyDevice(m_device, nullptr);
		vkDestroyInstance(m_instance, nullptr);
		return 0;
	}

	int VulkanApi::testDevice(VkPhysicalDevice device)
	{
		VkPhysicalDeviceProperties properties;
		vkGetPhysicalDeviceProperties(device, &properties);

		VkPhysicalDeviceFeatures features;
		vkGetPhysicalDeviceFeatures(device, &features);

		uint32_t graphicsQueue = getMatchingQueue(device, SE_VK_QUEUE_GRAPHICS);

		bool supportSwapchain = checkDeviceExtensionSupport({ VK_KHR_SWAPCHAIN_EXTENSION_NAME }, device);

		SE_CORE_INFO("Physical device: {}, api version: {}, geometry shader: {}, swap chain: {}", properties.deviceName, properties.apiVersion, features.geometryShader ? "yes" : "no", supportSwapchain ? "yes" : "no");
		return 1;
	}

	bool VulkanApi::checkValidationLayerSupport()
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

			if (!layerFound) {
				return false;
			}
		}

		return true;
	}

	bool VulkanApi::checkDeviceExtensionSupport(std::vector<const char*> deviceExtensions, VkPhysicalDevice device) {
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

		std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

		for (const auto& extension : availableExtensions) {
			requiredExtensions.erase(extension.extensionName);
		}

		return requiredExtensions.empty();
	}

	void VulkanApi::selectPhysicalDevice()
	{
		unsigned int devicesCount;
		vkEnumeratePhysicalDevices(m_instance, &devicesCount, nullptr);
		std::vector<VkPhysicalDevice> devices(devicesCount);
		vkEnumeratePhysicalDevices(m_instance, &devicesCount, devices.data());
		m_physicalDevice = nullptr;
		for (VkPhysicalDevice device : devices)
		{
			int deviceCapacity = testDevice(device);
			if (deviceCapacity > 0)
			{
				m_physicalDevice = device;
				break;
			}
		}
		if (!m_physicalDevice)
		{
			SE_CORE_CRITICAL("No physical device found with enough Vulkan support");
			throw std::runtime_error("No physical device found with enough Vulkan support");
		}
	}

	uint32_t VulkanApi::getMatchingQueue(VkPhysicalDevice device, enum SE_Vulkan_queue_types type)
	{
		uint32_t queueFamiliesCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamiliesCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamiliesCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamiliesCount, queueFamilies.data());

		uint32_t index = 0;
		for (VkQueueFamilyProperties property : queueFamilies)
		{
			switch (type)
			{
				case SE_VK_QUEUE_GRAPHICS:
				{
					if (property.queueFlags & VK_QUEUE_GRAPHICS_BIT)
					{
						return index;
					}
					break;
				}
				case SE_VK_QUEUE_PRESENTATION:
				{
					//VkBool32 presentSupport = false;
					//vkGetPhysicalDeviceSurfaceSupportKHR(device, index, surface, &presentSupport);
					if(glfwGetPhysicalDevicePresentationSupport(m_instance, m_physicalDevice, index))
						return index;
					break;
				}
			}
			index++;
		}
		SE_CORE_TRACE("Queue not found");
		return 0;
	}

	void VulkanApi::createDevice(std::vector<const char*> deviceExtensions)
	{
		uint32_t graphicsQueue     = getMatchingQueue(m_physicalDevice, SE_VK_QUEUE_GRAPHICS);
		uint32_t presentationQueue = getMatchingQueue(m_physicalDevice, SE_VK_QUEUE_PRESENTATION);
		SE_CORE_TRACE("Graphics queue: {} presentation queue: {}", graphicsQueue, presentationQueue);
		std::set<uint32_t> uniqueQueueFamilies = { graphicsQueue, presentationQueue };

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		queueCreateInfos.reserve(uniqueQueueFamilies.size());
		for (uint32_t queue : uniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queue;
			queueCreateInfo.queueCount = 1;
			float priority = 1.0f;
			queueCreateInfo.pQueuePriorities = &priority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures deviceFeatures{};

		VkDeviceCreateInfo createDeviceInfo{};
		createDeviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createDeviceInfo.pQueueCreateInfos = queueCreateInfos.data();
		createDeviceInfo.queueCreateInfoCount = (uint32_t)queueCreateInfos.size();
		createDeviceInfo.pEnabledFeatures = &deviceFeatures;
		createDeviceInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
		createDeviceInfo.ppEnabledExtensionNames = deviceExtensions.data();

		if (vkCreateDevice(m_physicalDevice, &createDeviceInfo, nullptr, &m_device) != VK_SUCCESS) {
			SE_CORE_CRITICAL("Failed to create vulkan device");
			throw std::runtime_error("failed to create logical device!");
		}

		vkGetDeviceQueue(m_device, graphicsQueue, 0, &m_graphicsQueue);
		vkGetDeviceQueue(m_device, presentationQueue, 0, &m_presentationQueue);
	}

	VkSurfaceKHR VulkanApi::createWindowSurface(GLFWwindow* window)
	{
		VkSurfaceKHR surface = nullptr;
		glfwCreateWindowSurface(m_instance, window, NULL, &surface);
		return surface;
	}

	void VulkanApi::destroyWindowSurface(VkSurfaceKHR surface)
	{
		vkDestroySurfaceKHR(m_instance, surface, nullptr);
	}
}