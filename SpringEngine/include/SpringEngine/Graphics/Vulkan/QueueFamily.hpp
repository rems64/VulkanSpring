#pragma once

namespace SE
{
	class Device;
	struct SE_API QueueFamilyRequirements;
	class SE_API QueueFamily
	{
	public:
		enum class Types
		{
			Graphics,
			Compute
		};
		QueueFamily(Device device, QueueFamilyRequirements requirements);
		~QueueFamily();

		uint32_t getQueueFamilyIndex() { return m_queueFamilyIndex; };
	private:
		uint32_t m_queueFamilyIndex;
	};

	struct QueueFamilyRequirements
	{
		QueueFamily::Types type;
		QueueFamilyRequirements(QueueFamily::Types type) : type(type) {};
	};
}