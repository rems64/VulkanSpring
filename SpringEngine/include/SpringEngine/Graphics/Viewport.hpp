#pragma once

namespace SE
{
	class SwapChain;
	class SE_API Viewport
	{
	public:
		Viewport(SwapChain* swapchain);
		~Viewport();

		static std::shared_ptr<Viewport> build(SwapChain* swapchain);
	private:
	};
}