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
		if (m_instance) // Check if there is no application already created
		{
			SE_CORE_CRITICAL("An instance of the application already exist, exiting");
			throw;
		}
		m_instance = this; // Kind of static class => only a unique instance of application should exist
		startup();
	}

	Application::~Application()
	{
		SE_CORE_INFO("Closing app...");
		Instrumentor::get().endSession();
	}

	void Application::startup()
	{
		m_running = true; // Variable that keep alive the main loop
		Instrumentor::get().beginSession("Application");
		SE_PROFILE_SCOPE("Initialise application");
		if (!glfwInit()) // Will be moved in a separate class soon
		{
			SE_CORE_CRITICAL("GLFW failed to initialize");
		}
		glfwSetErrorCallback(glfwErrorCallback); // Will be moved in a separate class soon

		m_renderingApi = RenderingApi::Api::Vulkan; // Will be better handled with the application creation refactor
		m_renderer = Renderer::build( { .api = m_renderingApi, .mode = Renderer::Modes::OnScreen, .type = Renderer::Types::Renderer2D, .surface = nullptr } );
		m_renderer->coreInit();

		std::shared_ptr<Window> defaultWindow = std::make_shared<Window>(WindowSpecs{ .title = "Vulkan powered window", .renderingApi = RenderingApi::Api::Vulkan, .width = 1600, .height = 900, .frameless = false, .fullscreen = false }); // Setup default window, will be improved soon to natively allow offscreen rendering
		m_windows.emplace_back(defaultWindow); // Will be handled automatically with the window management improvements

		m_renderer->setLinkedSurface(defaultWindow->getSurface());
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
		bool deleteWindows = false;
		for (std::vector<std::shared_ptr<Window>>::iterator window = m_windows.begin(); window!=m_windows.end(); window++)
		{
			if ((*window)->shouldClose())
			{
				pendingDelete.push_back(window);
				deleteWindows = true;
			}
			glfwPollEvents();
		}
		if (deleteWindows)
		{
			for (auto window : pendingDelete)
			{
				m_windows.erase(window);
			}
			m_running = !m_windows.empty();
		}
	}
}

void glfwErrorCallback(int error, const char* description)
{
	SE_CORE_ERROR("GLFW error: {}", description);
}