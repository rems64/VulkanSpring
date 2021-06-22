#pragma once

#include <SpringEngine/Graphics/Surface.hpp>

namespace SE
{
	class Swapchain;
	class Surface;
	class Window
	{
	public:
		Window();
		Window(const char* title, uint32_t width, uint32_t height);
		~Window();

		void init();
		bool shouldClose();

		GLFWwindow* getNative() { return m_window; };

	private:
		const char* m_name;
		uint32_t m_width;
		uint32_t m_height;
		GLFWwindow* m_window;
		std::shared_ptr<Surface> m_surface;
		bool m_shouldClose;
	};
}