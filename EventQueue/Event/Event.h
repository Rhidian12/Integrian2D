#pragma once

#include <string>

namespace Integrian2D
{
	class IEventData
	{
	public:
		virtual ~IEventData() = default;
	};

	template<typename Type>
	class EventData final : public IEventData
	{
	public:
		EventData(const Type& data)
			: m_Data{ data }
		{}

		const Type& GetData() const noexcept
		{
			return m_Data;
		}

	private:
		Type m_Data;
	};

	class Event final
	{
	public:
		template<typename Type>
		Event(const std::string& eventName, const Type& data)
			: m_Event{eventName}
			, m_pData{ new EventData<Type>{data} }
		{}

		Event(const Event&) = delete;
		Event& operator=(const Event&) = delete;

		Event(Event&& other) noexcept;
		Event& operator=(Event&& other) noexcept;

		~Event();

		const std::string& GetEvent() const noexcept;
		
		template<typename Type>
		const Type& GetData() const noexcept
		{
			return static_cast<EventData<Type>*>(m_pData)->GetData();
		}

	private:
		std::string m_Event;
		IEventData* m_pData;
	};
}