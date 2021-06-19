#pragma once

namespace SE
{
	class SE_API Renderer
	{
	public:
		Renderer();
		~Renderer();

		static std::shared_ptr<Renderer> build();
	};
}