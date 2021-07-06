#include <SpringEngine/Core/Window.hpp>

#include <SpringEngine/Core/Application.hpp>
#include <SpringEngine/Graphics/Surface.hpp>

namespace SE
{
	Window::Window() : m_specs{ .title = "Window", .width = 1280, .height = 720 }
	{
		init();
	}

	Window::Window(WindowSpecs specs) : m_specs(specs)
	{
		init();
	}

	Window::~Window()
	{
	}

	void Window::init()
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		if (m_specs.frameless)
			glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		m_window = glfwCreateWindow(m_specs.width, m_specs.height, m_specs.title, m_specs.fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
		if(!m_window)
			SE_CORE_CRITICAL("Failed to create GLFW window");
		m_surface = Surface::build({ .renderingApi = m_specs.renderingApi, .window = this });
		SE_CORE_INFO("New window alive");
	}

	bool Window::shouldClose()
	{
		return glfwWindowShouldClose(m_window);
	}

	Surface* Window::getSurface()
	{
		return nullptr;
	}
}