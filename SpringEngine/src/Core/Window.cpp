#include <SpringEngine/Core/Window.hpp>

#include <SpringEngine/Core/Application.hpp>
#include <SpringEngine/Graphics/Vulkan/VulkanApi.hpp>

namespace SE
{
	Window::Window() : m_width(1280), m_height(720), m_name("Window")
	{
		init();
	}

	Window::Window(const char* title, uint32_t width, uint32_t height) : m_width(width), m_height(height), m_name(title)
	{
		init();
	}

	Window::~Window()
	{
		switch (Application::getRenderingApi())
		{
		case RenderingApi::Api::SE_VULKAN:
		{
			break;
		}
		case RenderingApi::Api::SE_OPENGL:
		{
			break;
		}
		default:
			break;
		}
	}

	void Window::init()
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		m_window = glfwCreateWindow(m_width, m_height, m_name, nullptr, nullptr);
		if(!m_window)
			SE_CORE_CRITICAL("Failed to create GLFW window");
		SE_CORE_INFO("New window alive");
		switch (Application::getRenderingApi())
		{
			case RenderingApi::Api::SE_VULKAN:
			{
				break;
			}
			case RenderingApi::Api::SE_OPENGL:
			{
				break;
			}
			default:
				break;
		}
	}

	bool Window::shouldClose()
	{
		return glfwWindowShouldClose(m_window);
	}
}