#pragma once

namespace SE
{
	class SE_API RenderingApi
	{
	public:
		enum class Api
		{
			SE_VULKAN,
			SE_OPENGL
		};
	public:
		RenderingApi();
		virtual	~RenderingApi();

		std::shared_ptr<RenderingApi> static build();

		virtual int init() { return 0; };
		virtual int create() { return 0; };

		virtual int destroy() { return 0; };

		static RenderingApi::Api getApi() { return m_renderingApi; };

	private:
		static RenderingApi::Api m_renderingApi;
	};
}