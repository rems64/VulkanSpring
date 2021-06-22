#pragma once

namespace SE
{
	class SE_API Viewport
	{
	public:
		Viewport();
		~Viewport();

		std::shared_ptr<Viewport> build();
	private:
	};
}