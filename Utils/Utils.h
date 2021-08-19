#pragma once

#ifndef INTEGRIAN2D_UTILS_H
#define INTEGRIAN2D_UTILS_H

#include <type_traits>

namespace Integrian2D
{
	namespace Utils
	{
		// == Templated Functions ==
		template<typename Pointer>
		void SafeDelete(Pointer*& pData)
		{
			delete pData;
			pData = nullptr;
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
	}
}

#endif // !INTEGRIAN2D_UTILS_H