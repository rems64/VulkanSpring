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
			Compute,
			Presentation
		};
		QueueFamily(Device* device, QueueFamilyRequirements requirements);
		~QueueFamily();
		
		uint32_t selectQueue(std::vector<vk::QueueFamilyProperties>& queueFamilies, QueueFamilyRequirements requirements);
		uint32_t getQueueFamilyIndex() { return m_queueFamilyIndex; };
		float* getPriority() { return &m_priority; };
		QueueFamily::Types getType() { return m_type; };
	private:
		Device* m_device;
		QueueFamily::Types m_type;
		uint32_t m_queueFamilyIndex;
		float m_priority;
	};

	struct QueueFamilyRequirements
	{
		QueueFamily::Types type;
		QueueFamilyRequirements(QueueFamily::Types type) : type(type) {};
	};
}