#include <SpringEngine/Graphics/Vulkan/VulkanRenderer2D.hpp>

namespace SE
{
	VulkanRenderer2D::VulkanRenderer2D(Renderer::RendererSpecifications specs) : VulkanRenderer(specs)
	{

	}

	VulkanRenderer2D::~VulkanRenderer2D()
	{

	}

	int VulkanRenderer2D::init()
	{
		SE_VK_DEBUG(SE_CORE_TRACE("VulkanRenderer2D init (pre parent call)"));
		VulkanRenderer::init();
		return 0;
	}
}