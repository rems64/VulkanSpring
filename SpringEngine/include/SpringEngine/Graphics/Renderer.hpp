#pragma once

namespace SE
{
	class SE_API Renderer
	{
	public:
		Renderer();
		virtual ~Renderer();

		static std::shared_ptr<Renderer> build();
	};
}