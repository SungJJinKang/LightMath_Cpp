#pragma once
#include "Vector.h"

namespace Math
{
	template <typename T>
	struct Vector<4, T>
	{
		static_assert(std::is_arithmetic_v<T>);

		using value_type = typename T;
		using type = typename Vector<4, T>;

		value_type value[4];

		value_type& x = value[0];
		value_type& y = value[1];
		value_type& z = value[2];
		value_type& w = value[3];

		value_type& r = value[0];
		value_type& g = value[1];
		value_type& b = value[2];
		value_type& a = value[3];

		constexpr Vector() noexcept : value{}
		{

		}

		constexpr Vector(value_type x, value_type y, value_type z, value_type w) noexcept
		{
			value[0] = x;
			value[1] = y;
			value[2] = z;
			value[3] = w;
		}

		template <typename X>
		constexpr explicit Vector(const Vector<1, X>& vector) noexcept
		{
			x = vector.x;
			y = 0;
			z = 0;
			w = 0;
		}

		template <typename X>
		constexpr explicit Vector(const Vector<2, X>& vector) noexcept
		{
			x = vector.x;
			y = vector.y;
			z = 0;
			w = 0;
		}

		template <typename X>
		constexpr explicit Vector(const Vector<3, X>& vector) noexcept
		{
			x = vector.x;
			y = vector.y;
			z = vector.z;
			w = 0;
		}

		template <typename X>
		constexpr explicit Vector(const Vector<4, X>& vector) noexcept
		{
			x = vector.x;
			y = vector.y;
			z = vector.z;
			w = vector.w;
		}

// 		Vector(const type&) = default;
// 		Vector(type&&) = default;
// 		type& opreator=(const type&) = default;
// 		type& opreator=(type&&) = default;

		constexpr std::basic_string<char> toString() noexcept
		{
			std::stringstream ss;
			ss << x << "  " << y << "  " << z << "  " << w;
			return ss.str();
		}

		[[nodiscard]] inline static constexpr size_t length()  noexcept { return 4; }

		[[nodiscard]] value_type& operator[](size_t i)
		{
			assert(i >= 0 || i < length());
			return value[i];
		}

		[[nodiscard]] constexpr value_type& operator[](size_t i) const
		{
			assert(i >= 0 || i < length());
			return value[i];
		}

		

		[[nodiscard]] inline constexpr value_type sqrMagnitude() noexcept
		{
			return std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2) + std::pow(w, 2);
		}

		[[nodiscard]] inline constexpr value_type magnitude() noexcept
		{
			return std::pow(sqrMagnitude(), 2);
		}

		[[nodiscard]] constexpr type normalized()
		{
			value_type magnitude = magnitude();
			if (magnitude == 0)
				return type{};

			return type{ x / magnitude, y / magnitude, z / magnitude, w / magnitude };
		}

		constexpr type& Normalize()
		{
			value_type magnitude = magnitude();
			if (magnitude == 0)
				return *this;
			else
			{
				x = x / magnitude;
				y = y / magnitude;
				z = z / magnitude;
				w = w / magnitude;
				return *this;
			}
		}

		

		template <size_t RightComponentSize, typename X, typename std::enable_if_t<RightComponentSize >= 4, bool> = true>
		constexpr type& operator+=(const Vector<RightComponentSize, X>& rhs) noexcept
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			w += rhs.w;
			return *this;
		}

		template <size_t RightComponentSize, typename X, typename std::enable_if_t<RightComponentSize >= 4, bool> = true>
		constexpr type& operator-=(const Vector<RightComponentSize, X>& rhs) noexcept
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			w -= rhs.w;
			return *this;
		}

		template <size_t RightComponentSize, typename X, typename std::enable_if_t<RightComponentSize >= 4, bool> = true>
		constexpr type& operator*=(const Vector<RightComponentSize, X>& rhs) noexcept
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;
			w *= rhs.w;
			return *this;
		}

		template <size_t RightComponentSize, typename X, typename std::enable_if_t<RightComponentSize >= 4, bool> = true>
		constexpr type& operator/=(const Vector<RightComponentSize, X>& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			z /= rhs.z;
			w /= rhs.w;
			return *this;
		}

		template <size_t RightComponentSize, typename X, typename std::enable_if_t<RightComponentSize >= 4, bool> = true>
		constexpr type& operator%=(const Vector<RightComponentSize, X>& rhs)
		{
			x %= rhs.x;
			y %= rhs.y;
			z %= rhs.z;
			w %= rhs.w;
			return *this;
		}

		//

		constexpr type& operator+=(const value_type& scalar) noexcept
		{
			x += scalar;
			y += scalar;
			z += scalar;
			w += scalar;
			return *this;
		}

		constexpr type& operator-=(const value_type& scalar) noexcept
		{
			x -= scalar;
			y -= scalar;
			z -= scalar;
			w -= scalar;
			return *this;
		}
		
		constexpr type& operator*=(const value_type& scalar) noexcept
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;
			return *this;
		}

		constexpr type& operator/=(const value_type& scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
			w /= scalar;
			return *this;
		}

		constexpr type& operator%=(const value_type& scalar)
		{
			x %= scalar;
			y %= scalar;
			z %= scalar;
			w %= scalar;
			return *this;
		}

		//

		[[nodiscard]] inline constexpr bool operator==(const type& rhs) noexcept
		{
			return this.x == rhs.x && this.y == rhs.y && this.z == rhs.z && this.w == rhs.w;
		}

		[[nodiscard]] constexpr bool operator!=(const type& rhs) noexcept
		{
			return this.x != rhs.x || this.y != rhs.y || this.z != rhs.z || this.w != rhs.w;
		}

		/// <summary>
		/// prefix
		/// </summary>
		/// <returns></returns>
		constexpr type& operator++() noexcept
		{
			++x;
			++y;
			++z;
			++w;
			return *this;
		}

		/// <summary>
		/// postfix
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		constexpr type operator++(int) noexcept
		{
			type Vector{ *this };
			++* this;
			return Vector;
		}

		/// <summary>
		/// prefix
		/// </summary>
		/// <returns></returns>
		constexpr type& operator--() noexcept
		{
			--x;
			--y;
			--z;
			--w;
			return *this;
		}

		/// <summary>
		/// postfix
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		constexpr type operator--(int) noexcept
		{
			type Vector{ *this };
			--* this;
			return Vector;
		}
		
	};


}