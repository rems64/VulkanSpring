#pragma once

#include <SpringEngine/Graphics/RenderingApi.hpp>

namespace SE
{
	class SE_API VulkanApi : public RenderingApi
	{
	public:
		VulkanApi();
		~VulkanApi();

		virtual int init() override;
		virtual int create() override;
		virtual int destroy() override;

		static vk::Instance& getInstance() { return m_instance; };

		void setupValidationLayers();
		std::vector<vk::ExtensionProperties> getAvailableExtensions();
	private:
		std::vector<const char*> m_validationLayers;
		bool m_enableValidationLayers;

		static vk::Instance m_instance;
	};
}