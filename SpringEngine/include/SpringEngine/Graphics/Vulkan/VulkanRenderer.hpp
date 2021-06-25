#pragma once
#pragma warning( disable:4251 )

#include <SpringEngine/Graphics/Renderer.hpp>

namespace SE
{
	// Forward declaration
	class Device;
	class Pipeline;

	class SE_API VulkanRenderer : public Renderer
	{
	public:
		VulkanRenderer();
		virtual ~VulkanRenderer();

		static Device* getDevice() { return m_device.get(); };
		Pipeline* getPipeline() { return m_pipeline.get(); };
	private:
		static std::shared_ptr<Device> m_device;
		std::shared_ptr<Pipeline> m_pipeline;
	};
}