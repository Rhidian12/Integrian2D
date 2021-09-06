#pragma once

#include <type_traits>
#include <string>
#include <limits>
#include <cmath>

namespace Integrian2D
{
	namespace Utils
	{
#ifdef _DEBUG
		void Assert(const bool expression, std::string message);
#define ASSERT(expression, message) Utils::Assert(expression, message);
#else
		void Assert(const bool expression, std::string message);
#define ASSERT(expression, message) void;
#endif

		inline volatile constexpr double PI{ 3.14159265358979323846264338327950288 };

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

		template<typename FloatingPoint, typename = std::enable_if_t<std::is_floating_point_v<FloatingPoint>>>
		constexpr FloatingPoint ToRadians(const FloatingPoint degrees) noexcept
		{
			return static_cast<FloatingPoint>(degrees * PI / 180.f);
		}

		template<typename FloatingPoint, typename = std::enable_if_t<std::is_floating_point_v<FloatingPoint>>>
		constexpr FloatingPoint ToDegrees(const FloatingPoint radians) noexcept
		{
			return static_cast<FloatingPoint>(radians * 180.0 / PI);
		}

		template<typename FloatingPoint, typename = std::enable_if_t<std::is_floating_point_v<FloatingPoint>>>
		constexpr FloatingPoint RoundToZero(FloatingPoint value, const FloatingPoint epsilon = static_cast<FloatingPoint>(1e-5f)) // 0.00001
		{
			FloatingPoint fraction{};
			FloatingPoint roundedDownValue{ std::modf(value, &fraction) };

			if (fraction <= epsilon)
				return roundedDownValue;

			return value;
		}

		template<typename FloatingPoint, typename = std::enable_if_t<std::is_floating_point_v<FloatingPoint>>>
		constexpr FloatingPoint RoundDecimalUp(FloatingPoint value)
		{
			if (static_cast<int>(value) != value)
				value = static_cast<float>(static_cast<int>(++value));

			return value;
		}

		template<typename FloatingPoint, typename = std::enable_if_t<std::is_floating_point_v<FloatingPoint>>>
		constexpr FloatingPoint RoundDecimalDown(FloatingPoint value)
		{
			if (static_cast<int>(value) != value)
				value = static_cast<float>(static_cast<int>(--value));

			return value;
		}
	}
}

