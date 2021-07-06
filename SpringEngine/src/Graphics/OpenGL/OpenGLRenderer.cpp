#include <SpringEngine/Graphics/OpenGL/OpenGLRenderer.hpp>

namespace SE
{
	OpenGLRenderer::OpenGLRenderer(Renderer::RendererSpecifications specs) : Renderer(specs)
	{
		m_specs.api = RenderingApi::Api::OpenGL;
	}

	OpenGLRenderer::~OpenGLRenderer()
	{

	}

	int OpenGLRenderer::coreInit()
	{
		return 0;
	}

	int OpenGLRenderer::init()
	{
		m_renderingApi = makeShared<OpenGLApi>();
		m_renderingApi->init();
		return 0;
	}
}