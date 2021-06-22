#pragma once

namespace SE
{
	class Surface;
	class SwapChain
	{
	public:
		SwapChain(Surface* surface);
		~SwapChain();
		
		static std::shared_ptr<SwapChain> build(Surface* device);
	};
}