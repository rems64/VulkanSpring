#pragma once

namespace SE
{
	struct WindowSpecs
	{
		const char* title = "Default title";
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

	private:
		WindowSpecs m_specs;
		GLFWwindow* m_window;
		bool m_shouldClose;
	};
}