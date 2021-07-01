#include <SpringEngine/Graphics/Vulkan/VulkanApi.hpp>

#include <SpringEngine/Core/Application.hpp>

namespace SE
{
	PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT;
	PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT;

	vk::Instance VulkanApi::m_instance;
	VulkanApi::VulkanApi() : m_validationLayers{ "VK_LAYER_KHRONOS_validation" }
	{

	}

	VulkanApi::~VulkanApi()
	{

	}

	int VulkanApi::init()
	{
		createInstance();
		#ifdef SE_DEBUG
			setupDebugMessenger();
		#endif
		return 0;
	}

	int VulkanApi::destroy()
	{
		#ifdef SE_DEBUG
			SE_VK_DEBUG(SE_CORE_TRACE("Destroying vulkan messenger..."));
			vkDestroyDebugUtilsMessengerEXT(m_instance, (VkDebugUtilsMessengerEXT)m_debugMessenger, nullptr);
		#endif
		SE_VK_DEBUG(SE_CORE_INFO("Destroying instance..."));
		m_instance.destroy();
		return 0;
	}

	void VulkanApi::createInstance()
	{
		SE_VK_DEBUG(SE_CORE_INFO("Creating instance..."));
		vk::ApplicationInfo appInfo
		{
			.pApplicationName = Application::get()->getName(),
			.applicationVersion = VK_MAKE_VERSION(0, 1, 0),
			.pEngineName = "Spring Engine",
			.engineVersion = VK_MAKE_VERSION(0, 1, 0),
			.apiVersion = VK_MAKE_VERSION(1, 0, 0)
		};

		vk::InstanceCreateInfo createInfo
		{
			.pApplicationInfo = &appInfo
		};

		std::vector<const char*> extensions = getExtensions();

		createInfo.enabledExtensionCount = (uint32_t)extensions.size();
		createInfo.ppEnabledExtensionNames = extensions.data();
		
		#ifdef SE_DEBUG
			if (!checkValidationLayers())
			{
				SE_CORE_ERROR("Validation layers incomplete");
			}
			createInfo.enabledLayerCount = (uint32_t)m_validationLayers.size();
			createInfo.ppEnabledLayerNames = m_validationLayers.data();
		#else
			createInfo.enabledLayerCount = 0;
		#endif
		VK_CALL(m_instance = vk::createInstance(createInfo));
	}

	std::vector<const char*> VulkanApi::getExtensions()
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;

		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
		#ifdef SE_DEBUG
			extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		#endif

		return extensions;
	}


	bool VulkanApi::checkValidationLayers()
	{
		std::vector<vk::LayerProperties> availableValidationLayers = vk::enumerateInstanceLayerProperties();
		for (const char* layer : m_validationLayers)
		{
			bool found = false;
			for (const vk::LayerProperties& layerProperties : availableValidationLayers)
			{
				if (strcmp(layer, layerProperties.layerName) == 0)
				{
					found = true;
					break;
				}
			}
			if (!found)
				return false;
		}
		return true;
	}

	void VulkanApi::setupDebugMessenger()
	{
		#ifdef SE_DEBUG
			vk::DebugUtilsMessengerCreateInfoEXT createInfo
			{
				.messageSeverity = vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError | vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo,
				.messageType = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
				.pfnUserCallback = debugCallback,
				.pUserData = nullptr
			};
			//VkDebugUtilsMessengerEXT debugUtilsMessenger;

			vkCreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(m_instance, "vkCreateDebugUtilsMessengerEXT"));
			vkDestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(m_instance, "vkDestroyDebugUtilsMessengerEXT"));
			vkCreateDebugUtilsMessengerEXT((VkInstance)m_instance, (VkDebugUtilsMessengerCreateInfoEXT*)&createInfo, nullptr, (VkDebugUtilsMessengerEXT*)&m_debugMessenger);
		#endif
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL VulkanApi::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT type, const VkDebugUtilsMessengerCallbackDataEXT* callbackData, void* userData)
	{
		switch (severity)
		{
			case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
			{
				SE_CORE_TRACE("VULKAN : {}", callbackData->pMessage);
				break;
			}
			case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
			{
				SE_CORE_INFO("VULKAN : {}", callbackData->pMessage);
				break;
			}
			case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
			{
				SE_CORE_WARN("VULKAN : {}", callbackData->pMessage);
				break;
			}
			case VkDebugUtilsMessageSeverityFlagBitsEXT::VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
			{
				SE_CORE_ERROR("VULKAN : {}", callbackData->pMessage);
				break;
			}
		}
		return false;
	}
}