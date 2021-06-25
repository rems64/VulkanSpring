#include <SpringEngine/Graphics/Vulkan/VulkanSwapChain.hpp>

#include <SpringEngine/Graphics/Vulkan/VulkanSurface.hpp>
#include <SpringEngine/Graphics/Vulkan/Device.hpp>
#include <SpringEngine/Graphics/Vulkan/VulkanRenderer.hpp>
#include <SpringEngine/Core/Window.hpp>

namespace SE
{
	VulkanSwapChain::VulkanSwapChain(VulkanSurface* surface) : SwapChain(surface)
	{
		bool supported = VulkanRenderer::getDevice()->getSurfaceSupport(surface, VulkanRenderer::getDevice()->getQueueFamily(QueueFamily::Types::Graphics)->getQueueFamilyIndex());
		if (!supported)
		{
			SE_CORE_ERROR("Swap chain isn't supported on this device, this is an error please report");
		}
		std::vector<vk::SurfaceFormatKHR> availableFormats = VulkanRenderer::getDevice()->getSurfaceFormats(surface);
		std::vector<vk::PresentModeKHR> availablePresentModes = VulkanRenderer::getDevice()->getPresentModes(surface);
		vk::SurfaceCapabilitiesKHR capabilities = VulkanRenderer::getDevice()->getSurfaceCapabilities(surface);

		vk::SurfaceFormatKHR format;
		vk::PresentModeKHR presentMode;
		vk::Extent2D extend;

		for (vk::SurfaceFormatKHR& availableFormat : availableFormats)
		{
			if (availableFormat.format == vk::Format::eB8G8R8A8Srgb && availableFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
			{
				format = availableFormat;
			}
		}

		for (vk::PresentModeKHR& availablePresentMode : availablePresentModes)
		{
			if (availablePresentMode == vk::PresentModeKHR::eMailbox)
			{
				presentMode = availablePresentMode;
			}
		}

		if (capabilities.currentExtent.width != UINT32_MAX)
		{
			extend = capabilities.currentExtent;
		}
		else
		{
			int width, height;
			glfwGetFramebufferSize(surface->getWindow()->getNative(), &width, &height);

			VkExtent2D extend = {
				static_cast<uint32_t>(width),
				static_cast<uint32_t>(height)
			};

			extend.width = std::clamp(extend.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
			extend.height = std::clamp(extend.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
		}

		uint32_t imageCount = min(capabilities.minImageCount + 1, capabilities.maxImageCount);
		vk::SwapchainCreateInfoKHR swapChainCreateInfos{ .surface = *surface->get(),
														.minImageCount = imageCount,
														.imageFormat = format.format,
														.imageColorSpace = format.colorSpace,
														.imageExtent = extend,
														.imageArrayLayers = 1,
														.imageUsage = vk::ImageUsageFlagBits::eColorAttachment };

		uint32_t queueFamilyIndices[] = { VulkanRenderer::getDevice()->getQueueFamily(QueueFamily::Types::Graphics)->getQueueFamilyIndex(), VulkanRenderer::getDevice()->getQueueFamily(QueueFamily::Types::Presentation)->getQueueFamilyIndex() };
		if (VulkanRenderer::getDevice()->getQueueFamily(QueueFamily::Types::Graphics)->getQueueFamilyIndex() != VulkanRenderer::getDevice()->getQueueFamily(QueueFamily::Types::Graphics)->getQueueFamilyIndex()) {
			swapChainCreateInfos.setImageSharingMode(vk::SharingMode::eConcurrent);
			swapChainCreateInfos.setQueueFamilyIndexCount(2);
			swapChainCreateInfos.pQueueFamilyIndices = queueFamilyIndices;
		}
		else {
			swapChainCreateInfos.setImageSharingMode(vk::SharingMode::eExclusive);
			swapChainCreateInfos.queueFamilyIndexCount = 0; // Optional
			swapChainCreateInfos.pQueueFamilyIndices = nullptr; // Optional
		}
		swapChainCreateInfos.setPreTransform(capabilities.currentTransform);
		swapChainCreateInfos.setCompositeAlpha(vk::CompositeAlphaFlagBitsKHR::eOpaque);
		swapChainCreateInfos.setPresentMode(presentMode);
		swapChainCreateInfos.setClipped(true);
		swapChainCreateInfos.setOldSwapchain(nullptr);

		//vk::SwapchainKHR swapChain = VulkanRenderer::getDevice()->getDevice()->createSwapchainKHR(swapChainCreateInfos);
		m_swapChain = std::make_shared<vk::SwapchainKHR>(VulkanRenderer::getDevice()->getDevice()->createSwapchainKHR(swapChainCreateInfos));
		vkGetSwapchainImagesKHR(*VulkanRenderer::getDevice()->getDevice(), *m_swapChain.get(), &imageCount, nullptr);
		m_swapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(*VulkanRenderer::getDevice()->getDevice(), *m_swapChain.get(), &imageCount, (VkImage*)m_swapChainImages.data());

		m_swapChainImageViews.resize(imageCount);
		for (size_t i = 0; i < m_swapChainImages.size(); i++)
		{
			vk::ImageViewCreateInfo imageViewCreateInfos{ .image = m_swapChainImages[i],
														.viewType = vk::ImageViewType::e2D,
														.format = format.format,
														.components {
															.r = vk::ComponentSwizzle::eIdentity,
															.g = vk::ComponentSwizzle::eIdentity,
															.b = vk::ComponentSwizzle::eIdentity,
															.a = vk::ComponentSwizzle::eIdentity
														},
														.subresourceRange = {
															.aspectMask = vk::ImageAspectFlagBits::eColor,
															.baseMipLevel = 0,
															.levelCount = 1,
															.baseArrayLayer = 0,
															.layerCount = 1
														} };
			m_swapChainImageViews[i] = VulkanRenderer::getDevice()->getDevice()->createImageView(imageViewCreateInfos);
		}

		vk::AttachmentDescription colorAttachment
		{
			.format = format.format,
			.samples = vk::SampleCountFlagBits::e1,
			.loadOp = vk::AttachmentLoadOp::eClear,
			.storeOp = vk::AttachmentStoreOp::eStore,
			.stencilLoadOp = vk::AttachmentLoadOp::eDontCare,
			.stencilStoreOp = vk::AttachmentStoreOp::eDontCare,
			.initialLayout = vk::ImageLayout::eUndefined,
			.finalLayout = vk::ImageLayout::ePresentSrcKHR
		};

		vk::AttachmentReference colorAttachmentRef
		{
			.attachment = 0,
			.layout = vk::ImageLayout::eColorAttachmentOptimal
		};

		vk::SubpassDescription subpass
		{
			.pipelineBindPoint = vk::PipelineBindPoint::eGraphics,
			.colorAttachmentCount = 1,
			.pColorAttachments = &colorAttachmentRef
		};

		vk::RenderPassCreateInfo renderPassInfo
		{
			.attachmentCount = 1,
			.pAttachments = &colorAttachment,
			.subpassCount = 1,
			.pSubpasses = &subpass
		};

		m_renderPass = VulkanRenderer::getDevice()->getDevice()->createRenderPass(renderPassInfo);

	}

	VulkanSwapChain::~VulkanSwapChain()
	{
		for (auto imageView : m_swapChainImageViews)
		{
			VulkanRenderer::getDevice()->getDevice()->destroyImageView(imageView);
		}
		VulkanRenderer::getDevice()->getDevice()->destroySwapchainKHR(*m_swapChain.get());
		VulkanRenderer::getDevice()->getDevice()->destroyRenderPass(m_renderPass);
	}
}