#include <SpringEngine/Graphics/Surface.hpp>

namespace SE
{
	class SE_API VulkanSurface : public Surface
	{
	public:
		VulkanSurface(SurfaceSpecs requirements);
		virtual ~VulkanSurface();

		vk::SurfaceKHR* getSurfaceKHR() { return m_surface.get(); };
	private:
		Shared<vk::SurfaceKHR> m_surface;
	};
}