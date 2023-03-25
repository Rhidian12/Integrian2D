#pragma once

#include "BlackboardData.h"

#include <unordered_map>
#include <string>
#include <memory>

namespace Integrian2D
{
	class Blackboard final
	{
	public:
		template<typename T>
		void AddData(const std::string& id, const T& data)
		{
			m_pData.insert(std::make_pair(id, std::make_shared<BlackboardData<T>>(data)));
		}

		template<typename T>
		T& GetData(const std::string& id)
		{
			auto it{ m_pData.find(id) };

			__ASSERT(it != m_pData.cend(), std::string{ "Blackboard::GetData() > the string with id" } + id + " was not found!");

			return std::static_pointer_cast<BlackboardData<T>>(it->second)->GetData();
		}

		template<typename T>
		const T& GetData(const std::string& id) const
		{
			auto it{ m_pData.find(id) };

			__ASSERT(it != m_pData.cend(), std::string{ "Blackboard::GetData() > the string with id" } + id + " was not found!");
			
			return std::static_pointer_cast<BlackboardData<T>>(it->second)->GetData();
		}

		template<typename T>
		void ChangeData(const std::string& id, const T& data) noexcept
		{
			auto it{ m_pData.find(id) };
			
			ASSERT(it != m_pData.cend(), std::string{ "Blackboard::ChangeData() > the string with id" } + id + " was not found!");

			std::static_pointer_cast<BlackboardData<T>>(it->second)->ChangeData(data);
		}

	private:
		std::unordered_map<std::string, std::shared_ptr<IBlackboardData>> m_pData;
	};
}