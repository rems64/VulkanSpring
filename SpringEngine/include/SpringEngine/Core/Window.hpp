#pragma once

namespace SE
{
	class Swapchain;
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
		VkSurfaceKHR m_surface;
		GLFWwindow* m_window;
		std::shared_ptr<Swapchain> m_swapchain;
		bool m_shouldClose;
	};
}