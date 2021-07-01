#pragma once

#include <SpringEngine/Graphics/RenderingApi.hpp>

namespace SE
{
	class Surface;
	class SE_API Renderer
	{
	public:
		enum class Modes
		{
			OnScreen,
			OffScreen
		};
		enum class Types
		{
			Renderer2D,
			Renderer3D
		};
		struct RendererSpecifications
		{
			RenderingApi::Api api = RenderingApi::Api::Vulkan;
			Renderer::Modes mode = Renderer::Modes::OnScreen;
			Renderer::Types type = Renderer::Types::Renderer3D;
			Surface* surface;
		};
	public:
		Renderer(RendererSpecifications specs);
		~Renderer();

		RenderingApi::Api getApi() { return m_specs.api; };
		Renderer::Modes getMode() { return m_specs.mode; };
		Renderer::Types getType() { return m_specs.type; };
		Surface* getLinkinedSurface() { return m_specs.surface; };

		virtual int init() = 0;

		// BUILD
		static std::shared_ptr<Renderer> build(RendererSpecifications specs);

	protected:
		RendererSpecifications m_specs;
	};
}