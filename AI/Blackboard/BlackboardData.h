#pragma once

namespace Integrian2D
{
	class IBlackboardData
	{
	public:
		virtual ~IBlackboardData() = default;
	};

	template<typename T>
	class BlackboardData final : public IBlackboardData
	{
	public:
		BlackboardData(const T& data);

		void ChangeData(const T& data);

		T& GetData();
		const T& GetData() const;

	private:
		T m_Data;
	};

	template<typename T>
	BlackboardData<T>::BlackboardData(const T& data)
		: m_Data{ data }
	{}

	template<typename T>
	void BlackboardData<T>::ChangeData(const T & data)
	{
		m_Data = data;
	}

	template<typename T>
	T& BlackboardData<T>::GetData()
	{
		return m_Data;
	}

	template<typename T>
	const T& BlackboardData<T>::GetData() const
	{
		return m_Data;
	}
}