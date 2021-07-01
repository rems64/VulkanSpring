#pragma once

namespace SE
{
	class RenderingApi
	{
	public:
		enum class Api
		{
			None = 0,
			Vulkan = 1,
			OpenGL = 2
		};
	};
}