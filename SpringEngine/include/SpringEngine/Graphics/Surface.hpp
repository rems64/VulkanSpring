#pragma once

#include <SpringEngine/Graphics/RenderingApi.hpp>

namespace SE
{
	class Window;
	struct SurfaceSpecs
	{
		RenderingApi::Api renderingApi;
		Window* window;
	};
	class SE_API Surface
	{
	public:
		Surface(SurfaceSpecs requirements);
		virtual ~Surface();

		static Shared<Surface> build(SurfaceSpecs requirements);
	};
}