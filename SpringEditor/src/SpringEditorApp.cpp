#include <SpringEngine/SpringEngine.hpp>
#include <SpringEngine/Core/EntryPoint.hpp>

class SpringEditorApp : public SE::Application
{
public:
	SpringEditorApp() : SE::Application("Spring editor")
	{
		SE_PROFILE_FUNCTION();
	}

	~SpringEditorApp()
	{

	}
};

SE::Application* SE::createApp()
{
	SE::Application* application = new SpringEditorApp();
	return application;
}