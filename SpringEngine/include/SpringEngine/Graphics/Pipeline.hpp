#pragma once

namespace SE
{
	class SE_API Pipeline
	{
	public:
		Pipeline();
		~Pipeline();

		std::shared_ptr<Pipeline> build();
	};
}