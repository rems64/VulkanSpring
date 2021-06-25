#pragma once

#include <SpringEngine/Core/Rect2D.hpp>

namespace SE
{
	class Surface;
	class SwapChain
	{
	public:
		SwapChain(Surface* surface);
		virtual ~SwapChain();
		
		static std::shared_ptr<SwapChain> build(Surface* device);
		Rect2Dui getExtent() { return m_extent; };
	protected:
		Rect2Dui m_extent;
	};
}