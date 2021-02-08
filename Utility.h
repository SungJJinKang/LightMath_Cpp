#pragma once
#include <limits>
#include <algorithm>

#include "LMath_Core.h"

namespace math
{
	inline constexpr float PI = 3.14159265358979323846f;

	inline constexpr float DEGREE_TO_RADIAN = PI / 180.0f;

	inline constexpr float RADIAN_TO_DEGREE = 180.0f / PI;

	

	template<typename T>
	inline constexpr typename std::enable_if_t<CHECK_IS_NUMBER(T), T> epsilon()
	{
		return std::numeric_limits<T>::epsilon();
	}

	template<typename T>
	inline constexpr typename std::enable_if_t<CHECK_IS_NUMBER(T), T> abs(T value)
	{
		return std::abs(value);
	}

	

	template<typename T>
	inline constexpr auto acos(T value)
	{
		return std::acos(value);
	}
	template<typename T>
	inline constexpr auto asin(T value)
	{
		return std::asin(value);
	}
	template<typename T>
	inline constexpr auto atan(T value)
	{
		return std::atan(value);
	}
	template<typename T>
	inline constexpr auto atan2(T value1, T value2)
	{
		return std::atan2(value1, value2);
	}

	template<typename T, typename Limit, typename std::enable_if_t<std::is_arithmetic_v<Limit>, bool> = true>
	inline constexpr typename std::enable_if_t<CHECK_IS_NUMBER(T), T> clamp(T value, Limit min, Limit max)
	{
		if (value < min)
			return min;
		else if (value > max)
			return max;
		return value;
	}

	template<typename T>
	inline constexpr typename std::enable_if_t<CHECK_IS_NUMBER(T), T> clamp01(T value)
	{
		return Clamp(value, T{ 0 }, T{ 1 });
	}

	template<typename T>
	inline constexpr auto cos(T radian)
	{
		return std::cos(radian);
	}


	template<typename T>
	inline constexpr typename std::enable_if_t<CHECK_IS_NUMBER(T), T> exp(T value)
	{
		return std::exp(value);
	}

	template<typename T>
	inline constexpr typename std::enable_if_t<CHECK_IS_NUMBER(T), T> infinity()
	{
		return (std::numeric_limits<T>::max)();
	} 

	template<typename T>
	inline constexpr typename std::enable_if_t<CHECK_IS_NUMBER(T), T> negativeInfinity()
	{
		return std::numeric_limits<T>::lowest();

	}


	template<typename Value, typename Floating, typename std::enable_if_t<std::is_floating_point_v<Floating>, bool> = true>
	inline constexpr typename std::enable_if_t<std::is_arithmetic_v<Value>, Value> lerpUnClamped(Value value1, Value value2, Floating t)
	{
		return value1 + t * (value2 - value1);
	}

	template<typename Value, typename Floating, typename std::enable_if_t<std::is_floating_point_v<Floating>, bool> = true>
	inline constexpr typename std::enable_if_t<std::is_arithmetic_v<Value>, Value> lerp(Value value1, Value value2, Floating t)
	{
		return lerpUnClamped<Value, Floating>(value1, value2, clamp01<Floating>(t));
	}

	

	template<typename T>
	inline constexpr auto log(T value)
	{
		return std::log(value);
	}

	template<typename T>
	inline constexpr auto log10(T value)
	{
		return std::log10(value);
	}

	template<typename X, typename Y>
	inline constexpr auto max(X x, Y y)
	{
		return (std::max)(x, y);
	}

	template<typename X, typename Y>
	inline constexpr auto min(X x, Y y)
	{
		return (std::min)(x, y);
	}

	template<typename T>
	inline constexpr typename std::enable_if_t<CHECK_IS_NUMBER(T), T> PerlinNoise(T value);

	template<typename X, typename Y>
	inline constexpr auto pow(X value, Y exp)
	{
		return std::pow(value, exp);
	}

	template<typename T>
	inline constexpr auto sin(T radian)
	{
		return std::sin(radian);
	}


	template<typename T>
	inline constexpr auto sqrt(T value)
	{
		return std::sqrt(value);
	}

	template<typename T>
	inline constexpr auto inverseSqrt(T value)
	{
		return static_cast<T>(1) / std::sqrt(value);
	}

	template<typename T>
	inline constexpr auto tan(T radian)
	{
		return std::tan(radian);
	}


}