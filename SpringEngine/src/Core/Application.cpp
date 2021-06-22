#include <SpringEngine/Core/Application.hpp>

#include <SpringEngine/Core/Window.hpp>
#include <SpringEngine/Graphics/Renderer.hpp>

namespace SE
{
	Application* Application::m_instance = nullptr;
	Application::Application() : m_name("Application"), m_renderingApi()
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

	Application::Application(const char* name) : m_name(name), m_renderingApi()
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
		m_renderer->~Renderer();
		m_renderingApi->~RenderingApi();
	}

	void Application::selectRenderingApi(RenderingApi::Api api)
	{
		switch (api)
		{
			case RenderingApi::Api::SE_VULKAN: m_settings.renderingApi = RenderingApi::Api::SE_VULKAN;
			case RenderingApi::Api::SE_OPENGL: m_settings.renderingApi = RenderingApi::Api::SE_OPENGL;
		}
	}

	enum RenderingApi::Api Application::getRenderingApi()
	{
		return m_instance->m_renderingApi->getApi();
	}

	void Application::startup()
	{
		m_running = true;
		m_settings.renderingApi = RenderingApi::Api::SE_VULKAN;
		if (!glfwInit())
		{
			SE_CORE_CRITICAL("GLFW failed to initialize");
		}
		glfwSetErrorCallback(glfwErrorCallback);
		m_renderingApi = RenderingApi::build();
		m_renderingApi->init();
		m_renderingApi->create();

		m_renderer = Renderer::build();

		std::shared_ptr<Window> defaultWindow = std::make_shared<Window>("Vulkan powered window", 1280, 720);
		m_windows.emplace_back(defaultWindow);

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