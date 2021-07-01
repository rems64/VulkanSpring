#include <SpringEngine/Core/Application.hpp>

#include <SpringEngine/Core/Window.hpp>
#include <SpringEngine/Graphics/Renderer.hpp>

namespace SE
{
	Application* Application::m_instance = nullptr;
	Application::Application() : m_name("Application")
	{
		SE_PROFILE_FUNCTION();
		Log::init();
		SE_CORE_INFO("Application started");
		if (m_instance)
		{
			SE_CORE_CRITICAL("An instance of the application already exist, exiting");
			throw;
		}
		m_instance = this;
		startup();
	}

	Application::Application(const char* name) : m_name(name)
	{
		Log::init();
		SE_CORE_INFO("Application started");
		if (m_instance)
		{
			SE_CORE_CRITICAL("An instance of the application already exist, exiting");
			throw;
		}
		m_instance = this;
		startup();
	}

	Application::~Application()
	{
		SE_CORE_INFO("Closing app...");
	}

	void Application::startup()
	{
		m_running = true;
		if (!glfwInit())
		{
			SE_CORE_CRITICAL("GLFW failed to initialize");
		}
		glfwSetErrorCallback(glfwErrorCallback);

		std::shared_ptr<Window> defaultWindow = std::make_shared<Window>(WindowSpecs{ .title = "Vulkan powered window", .width = 1600, .height = 900, .frameless = false, .fullscreen = false });
		m_windows.emplace_back(defaultWindow);

		m_renderingApi = RenderingApi::Api::Vulkan;
		//m_renderer = Renderer::build(m_renderingApi, defaultWindow.get());
		m_renderer = Renderer::build( { .api = m_renderingApi, .mode = Renderer::Modes::OnScreen, .type = Renderer::Types::Renderer2D, .surface = nullptr } );
		m_renderer->init();
	}

	void Application::run()
	{
		SE_PROFILE_FUNCTION();
		while(m_running)
		{
			frame();
		}
	}

	void Application::frame()
	{
		SE_PROFILE_FUNCTION();
		std::vector<std::vector<std::shared_ptr<Window>>::iterator> pendingDelete;
		for (std::vector<std::shared_ptr<Window>>::iterator window = m_windows.begin(); window!=m_windows.end(); window++)
		{
			if ((*window)->shouldClose())
			{
				//m_windows.erase(window);
				pendingDelete.push_back(window);
			}
			glfwPollEvents();
		}
		for (auto window : pendingDelete)
		{
			m_windows.erase(window);
		}
		m_running = !m_windows.empty();
	}
}

void glfwErrorCallback(int error, const char* description)
{
	SE_CORE_ERROR("GLFW error: {}", description);
}