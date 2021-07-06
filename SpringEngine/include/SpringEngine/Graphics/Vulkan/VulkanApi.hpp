#pragma once

#include <SpringEngine/Graphics/RenderingApi.hpp>

namespace SE
{
	class SE_API VulkanApi : public RenderingApi
	{
	public:
		VulkanApi();
		~VulkanApi();

		int init();
		int destroy();

		void createInstance();
		std::vector<const char*> getExtensions();
		std::vector<vk::ExtensionProperties> getAvailableExtension();
		bool checkValidationLayers();
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT severity, VkDebugUtilsMessageTypeFlagsEXT type, const VkDebugUtilsMessengerCallbackDataEXT* callbackData, void* userData);
		void setupDebugMessenger();
		static vk::Instance* getInstance() { return &m_instance; };
	private:
		static vk::Instance m_instance;
		const std::vector<const char*> m_validationLayers;
		vk::DebugUtilsMessengerEXT m_debugMessenger;
	};
}