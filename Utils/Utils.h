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
#define ASSERT(expression, message)
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

		template<typename Type>
		constexpr Type Square(const Type value) noexcept
		{
			return value * value;
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
		constexpr FloatingPoint RoundToZero(FloatingPoint value, const FloatingPoint epsilon = static_cast<FloatingPoint>(1e-5f) /* == 0.00001 */) noexcept
		{
			FloatingPoint fraction{};
			FloatingPoint roundedDownValue{ std::modf(value, &fraction) };

			if (fraction <= epsilon)
				return roundedDownValue;

			return value;
		}

		template<typename FloatingPoint, typename = std::enable_if_t<std::is_floating_point_v<FloatingPoint>>>
		constexpr FloatingPoint RoundDecimalUp(FloatingPoint value) noexcept
		{
			if (static_cast<int>(value) != value)
				value = static_cast<FloatingPoint>(static_cast<int>(++value));

			return value;
		}

		template<typename FloatingPoint, typename = std::enable_if_t<std::is_floating_point_v<FloatingPoint>>>
		constexpr FloatingPoint RoundDecimalDown(FloatingPoint value) noexcept
		{
			if (static_cast<int>(value) != value)
				value = static_cast<FloatingPoint>(static_cast<int>(--value));

			return value;
		}

		template<typename Type>
		constexpr bool IsInRange(const Type value, const Type min, const Type max, const bool rangeLimitsInclusive = true) noexcept
		{
			if (rangeLimitsInclusive)
			{
				if (value >= min && value <= max)
					return true;
				else
					return false;
			}
			else
			{
				if (value > min && value < max)
					return true;
				else
					return false;
			}
		}

		template<typename Container, typename Predicate, typename key = typename Container::key_type, typename value = typename Container::mapped_type,
			typename = std::enable_if_t<std::is_invocable_r_v<bool, Predicate, const std::pair<key, value>&>>>
		constexpr void Erase_If(Container& items, const Predicate& predicate)
		{
			for (auto it{ items.begin() }; it != items.end();)
			{
				if (predicate(*it))
					it = items.erase(it);
				else
					++it;
			}
		}
	}
}

