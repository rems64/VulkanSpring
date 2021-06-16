#pragma once

#include <SpringEngine/Graphics/RenderingApi.hpp>

namespace SE
{
	enum SE_Vulkan_queue_types
	{
		SE_VK_QUEUE_GRAPHICS,
		SE_VK_QUEUE_PRESENTATION
	};

	class SE_API VulkanApi : public RenderingApi
	{
	public:
		VulkanApi();
		~VulkanApi();

		virtual int init() override;
		virtual int create() override;
		virtual int destroy() override;

		int testDevice(VkPhysicalDevice device);
		bool checkValidationLayerSupport();

		void selectPhysicalDevice();
		void createDevice(std::vector<const char*> deviceExtensions);
		uint32_t getMatchingQueue(VkPhysicalDevice device, SE_Vulkan_queue_types type);
		bool checkDeviceExtensionSupport(std::vector<const char*> deviceExtensions, VkPhysicalDevice device);

		static VkSurfaceKHR createWindowSurface(GLFWwindow* window);
		static void destroyWindowSurface(VkSurfaceKHR surface);

		VkInstance getInstance() { return m_instance; };
		VkDevice getDevice() { return m_device;	};
		VkPhysicalDevice getPhysicalDevice() { return m_physicalDevice;	};
		VkQueue getGraphicsQueue() { return m_graphicsQueue; };
		VkQueue getPresentationQueue() { return m_presentationQueue; };
	private:
		static VkInstance m_instance;
		VkApplicationInfo m_appInfo;
		VkInstanceCreateInfo m_createInfo;
		VkPhysicalDevice m_physicalDevice;
		VkDevice m_device;
		VkQueue m_graphicsQueue;
		VkQueue m_presentationQueue;
		std::vector<const char*> m_validationLayers;
		bool m_enableValidationLayers;
	};
}