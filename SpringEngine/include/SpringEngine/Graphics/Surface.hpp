#pragma once

namespace SE
{
	class Window;
	class Surface
	{
	public:
		Surface(Window* window);
		virtual ~Surface();

		static std::shared_ptr<Surface> build(Window* window);
		Window* getWindow() { return m_linkedWindow; };
	private:
		Window* m_linkedWindow;
	};
}