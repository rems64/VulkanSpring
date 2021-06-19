#pragma once

namespace SE
{
	// Forward declaration
	class Device;

	class SE_API VulkanRenderer
	{
		VulkanRenderer();
		~VulkanRenderer();
	private:
		Device m_device;
	};
}