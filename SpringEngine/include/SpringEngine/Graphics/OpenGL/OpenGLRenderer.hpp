#pragma once

#pragma warning( disable:4251 )
#include <SpringEngine/Graphics/Renderer.hpp>
#include <SpringEngine/Graphics/OpenGL/OpenGLApi.hpp>

namespace SE
{
	class SE_API OpenGLRenderer : public Renderer
	{
	public:
		OpenGLRenderer(Renderer::RendererSpecifications specs);
		~OpenGLRenderer();

		virtual int init() override;
	private:
		Shared<OpenGLApi> m_renderingApi;
	};
}