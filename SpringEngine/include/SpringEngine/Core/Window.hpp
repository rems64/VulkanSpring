#pragma once

#include <SpringEngine/Graphics/RenderingApi.hpp>

namespace SE
{
	class Surface;
	struct WindowSpecs
	{
		const char* title = "Default title";
		RenderingApi::Api renderingApi = RenderingApi::Api::Vulkan;
		uint32_t width;
		uint32_t height;
		bool frameless = false;
		bool fullscreen = false;
	};
	class Window
	{
	public:
		Window();
		Window(WindowSpecs);
		~Window();

		void init();
		bool shouldClose();

		GLFWwindow* getNative() { return m_window; };
		Surface* getSurface();

	private:
		WindowSpecs m_specs;
		GLFWwindow* m_window;
		Shared<Surface> m_surface;
		bool m_shouldClose;
	};
}