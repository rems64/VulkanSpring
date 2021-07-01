#include <SpringEngine/Graphics/OpenGL/OpenGLApi.hpp>

#include <GL/glew.h>
#include <GL/GL.h>

namespace SE
{
	OpenGLApi::OpenGLApi()
	{

	}

	OpenGLApi::~OpenGLApi()
	{

	}

	int OpenGLApi::init()
	{
		if (!glewInit())
		{
			SE_CORE_CRITICAL("Failed to initialize glew");
			return -1;
		}
		return 0;
	}
}