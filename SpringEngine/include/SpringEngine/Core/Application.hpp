#pragma once

#include <SpringEngine/Graphics/RenderingApi.hpp>
#pragma warning( disable:4251 )

namespace SE
{
	class Window;
	struct SE_ApplicationSettings
	{
		RenderingApi::Api renderingApi;
	};
	class SE_API Application
	{
	public:
		Application();
		Application(const char* name);
		~Application();

		static enum RenderingApi::Api getRenderingApi();
		static const char* getName() { return m_instance->m_name; };
		void selectRenderingApi(enum RenderingApi::Api api);

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
		std::shared_ptr<RenderingApi> m_renderingApi;
		struct SE_ApplicationSettings m_settings;
		std::vector<std::shared_ptr<Window>> m_windows;
		bool m_running;
	};

	// To be defined in client app
	Application* createApp();
}

void SE_API glfwErrorCallback(int error, const char* description);