#pragma once
#pragma warning( disable:4251 )

#include <SpringEngine/Graphics/Renderer.hpp>

namespace SE
{
	// Forward declaration
	class Device;

	class SE_API VulkanRenderer : public Renderer
	{
	public:
		VulkanRenderer();
		virtual ~VulkanRenderer();

		static Device* getDevice() { return m_device.get(); };
	private:
		static std::shared_ptr<Device> m_device;
	};
}