#pragma once

#include <type_traits>
#include <string>

namespace Integrian2D
{
	namespace Utils
	{
#ifdef _DEBUG
		void Assert(const bool expression, std::string message);
#else
		void Assert(const bool expression, std::string message);
#endif

		// == Templated Functions ==
		template<typename Pointer>
		void SafeDelete(Pointer*& pData)
		{
			if (pData)
			{
				delete pData;
				pData = nullptr;
			}
		}

		template<typename FundamentalType, typename = std::enable_if_t<std::is_fundamental_v<FundamentalType>>>
		constexpr FundamentalType RandomNumber(const FundamentalType min, const FundamentalType max)
		{
			if constexpr (std::is_floating_point_v<FundamentalType>)
			{
				// https://stackoverflow.com/questions/686353/random-float-number-generation
				return min + static_cast<FundamentalType>(rand()) / (static_cast<FundamentalType>(RAND_MAX / (max - min)));
			}
			else
			{
				return static_cast<FundamentalType>(rand()) % max + min;
			}
		}

		template<typename Type>
		constexpr void Clamp(Type& value, const Type& min, const Type& max) noexcept
		{
			if (value < min)
				value = min;

			if (value > max)
				value = max;
		}

		template<typename FundamentalType, typename = std::enable_if_t<std::is_fundamental_v<FundamentalType>>>
		constexpr bool AreEqual(const FundamentalType a, const FundamentalType b)
		{
			return abs(a - b) <= std::numeric_limits<FundamentalType>::epsilon();
		}
	}
}

