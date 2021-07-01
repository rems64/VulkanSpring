#pragma once

#pragma warning( disable:4251 )
#include <SpringEngine/Graphics/RenderingApi.hpp>

namespace SE
{
	class Window;
	class Renderer;
	struct SE_ApplicationSettings
	{
	};
	class SE_API Application
	{
	public:
		Application();
		Application(const char* name);
		~Application();

		static const char* getName() { return m_instance->m_name; };

		void startup();
		void run();
		void frame();

		static Application* get() { return m_instance; };
	private:
		Application(const Application&);
		Application& operator=(const Application& right);
		void initGraphicsAPI();
	private:
		static Application* m_instance;
		const char* m_name;
		struct SE_ApplicationSettings m_settings;
		bool m_running;

		std::vector<std::shared_ptr<Window>> m_windows;
		RenderingApi::Api m_renderingApi;
		std::shared_ptr<Renderer> m_renderer;
	};

	// To be defined in client app
	Application* createApp();
}

void SE_API glfwErrorCallback(int error, const char* description);