#pragma once

namespace SE
{
	class SE_API Surface
	{
	public:
		Surface();
		~Surface();

		Shared<Surface> build();
	};
}