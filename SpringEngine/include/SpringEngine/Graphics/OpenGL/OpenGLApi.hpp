#pragma once

#include <SpringEngine/Graphics/RenderingApi.hpp>

namespace SE
{
	class OpenGLApi : public RenderingApi
	{
	public:
		OpenGLApi();
		~OpenGLApi();

		int init();
	private:
	};
}