#pragma once
#include "Matrix.h"

#include "Vector1.h"
namespace Math
{
	template <typename T>
	struct Matrix<1, 1, T>
	{
		static_assert(CHECK_IS_NUMBER(T));
		static_assert(CHECK_IS_NOT_CV(T));

		using value_type = typename T;
		using type = typename Matrix<1, 1, T>;
		template <typename T2>
		using col_type_template = Vector<1, T2>;
		using col_type = Vector<1, T>;
		
		[[nodiscard]] inline static constexpr size_t collumCount()  noexcept { return 1; }
		col_type collums[1]; // don't change to collum

		constexpr Matrix() noexcept : collums{}
		{

		}

		constexpr explicit Matrix(value_type value) noexcept
		{
			collums[0] = value;
		}

		template <typename X>
		constexpr Matrix(X value) noexcept
		{
			collums[0] = static_cast<T>(value);
		}


		constexpr Matrix(col_type collum0Value) noexcept
		{
			collums[0] = collum0Value;
		}

		template <typename X>
		constexpr Matrix(col_type_template<X> collum0) noexcept
		{
			collums[0] = collum0;
		}

		constexpr explicit Matrix(const Matrix<1, 1, T>& matrix) noexcept
		{
			collums[0] = matrix.collums[0];
		}

		template <typename X>
		constexpr Matrix(const Matrix<1, 1, X>& matrix) noexcept
		{
			collums[0] = matrix.collums[0];
		}

		template <typename X>
		constexpr Matrix(const Matrix<2, 2, X>& matrix) noexcept
		{
			collums[0] = matrix.collums[0];
		}

		template <typename X>
		constexpr Matrix(const Matrix<3, 3, X>& matrix) noexcept
		{
			collums[0] = matrix.collums[0];
		}

		template <typename X>
		constexpr Matrix(const Matrix<4, 4, X>& matrix) noexcept
		{
			collums[0] = matrix.collums[0];
		}

		constexpr type& operator=(value_type value) noexcept
		{
			collums[0] = value;
			return *this;
		}

		constexpr type& operator=(const Matrix<1, 1, T>& matrix) noexcept
		{
			collums[0] = matrix.collums[0];
			return *this;
		}

		template <typename X>
		constexpr type& operator=(const Matrix<1, 1, X>& matrix) noexcept
		{
			collums[0] = matrix.collums[0];
			return *this;
		}

		template <typename X>
		constexpr type& operator=(const Matrix<2, 2, X>& matrix) noexcept
		{
			collums[0] = matrix.collums[0];
			return *this;
		}

		template <typename X>
		constexpr type& operator=(const Matrix<3, 3, X>& matrix) noexcept
		{
			collums[0] = matrix.collums[0];
			return *this;
		}

		template <typename X>
		constexpr type& operator=(const Matrix<4, 4, X>& matrix) noexcept
		{
			collums[0] = matrix.collums[0];
			return *this;
		}

		// 		Matrix(const type&) = default;
		// 		Matrix(type&&) = default;
		// 		type& opreator=(const type&) = default;
		// 		type& opreator=(type&&) = default;

		constexpr std::basic_string<char> toString() noexcept
		{
			std::stringstream ss;
			ss << collums[0].x << '\n';
			return ss.str();
		}

		[[nodiscard]] col_type& operator[](size_t i)
		{
			assert(i == 0);
			return collums[i];
		}

		[[nodiscard]] constexpr const col_type& operator[](size_t i) const
		{
			assert(i == 0);
			return collums[i];
		}



		template <typename X>
		constexpr type operator+(const Matrix<1, 1, X>& rhs) noexcept
		{
			return type(collums[0] + rhs.collums[0]);
		}

		template <typename X>
		constexpr type operator-(const Matrix<1, 1, X>& rhs) noexcept
		{
			return type(collums[0] - rhs.collums[0]);
		}

		template <typename X>
		constexpr type operator*(const Matrix<1, 1, X>& rhs) noexcept
		{
			return Matrix<1, 1, T>(collums[0] * rhs.collums[0]);
		}


		/*
		template <typename X>
		constexpr type operator/(const Matrix<4, X>& rhs)
		{
			return type(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
		}

		template <typename X>
		constexpr type operator%(const Matrix<4, X>& rhs)
		{
			return type(x % rhs.x, y % rhs.y, z % rhs.z, w % rhs.w);
		}
		*/

		template <typename X>
		constexpr type& operator+=(const Matrix<1, 1, X>& rhs) noexcept
		{
			collums[0] += rhs.collums[0];
			return *this;
		}

		template <typename X>
		constexpr type& operator-=(const Matrix<1, 1, X>& rhs) noexcept
		{
			collums[0] -= rhs.collums[0];
			return *this;
		}


		template <typename X>
		constexpr type& operator*=(const Matrix<1, 1, X>& rhs) noexcept
		{
			return (*this = *this * rhs);
		}



		/*
		template <typename X>
		constexpr type& operator/=(const Matrix<4, X>& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			z /= rhs.z;
			w /= rhs.w;
			return *this;
		}

		template <typename X>
		constexpr type& operator%=(const Matrix<4, X>& rhs)
		{
			x %= rhs.x;
			y %= rhs.y;
			z %= rhs.z;
			w %= rhs.w;
			return *this;
		}
		*/
		//

		template <typename X>
		constexpr type& operator+=(const X& scalar) noexcept
		{
			collums[0] += scalar;
			return *this;
		}

		template <typename X>
		constexpr type& operator-=(const X& scalar) noexcept
		{
			collums[0] -= scalar;
			return *this;
		}

		template <typename X>
		constexpr type& operator*=(const X& scalar) noexcept
		{
			collums[0] *= scalar;
			return *this;
		}

		/*
		template <typename X>
		constexpr type& operator/=(const X& scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
			w /= scalar;
			return *this;
		}


		template <typename X, std::enable_if_t<std::is_integral_v<X>, bool> = true>
		constexpr type& operator%=(const X& scalar)
		{
			x %= scalar;
			y %= scalar;
			z %= scalar;
			w %= scalar;
			return *this;
		}

		template <typename X, std::enable_if_t<std::is_floating_point_v<X>, bool> = true>
		constexpr type& operator%=(const X& scalar)
		{

			x %= std::fmod(x, scalar);
			y %= std::fmod(y, scalar);
			z %= std::fmod(z, scalar);
			w %= std::fmod(w, scalar);
			return *this;
		}
		*/

		//

		[[nodiscard]] inline constexpr bool operator==(const type& rhs) noexcept
		{
			return this->collums[0] == rhs.collums[0];
		}

		[[nodiscard]] constexpr bool operator!=(const type& rhs) noexcept
		{
			return this->collums[0] != rhs.collums[0];
		}

		/// <summary>
		/// prefix
		/// </summary>
		/// <returns></returns>
		constexpr type& operator++() noexcept
		{
			++collums[0];
			return *this;
		}

		/// <summary>
		/// postfix
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		constexpr type operator++(int) noexcept
		{
			type Matrix{ *this };
			++* this;
			return Matrix;
		}

		/// <summary>
		/// prefix
		/// </summary>
		/// <returns></returns>
		constexpr type& operator--() noexcept
		{
			--collums[0];
			return *this;
		}

		/// <summary>
		/// postfix
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		constexpr type operator--(int) noexcept
		{
			type Matrix{ *this };
			--* this;
			return Matrix;
		}

		constexpr operator std::basic_string<char>() noexcept
		{
			return this->toString();
		}

		/*
		constexpr type inverse()
		{
			return type{ *this };
		}

		constexpr type transpose()
		{
			return type{ *this };
		}
		*/
	};

	template<typename T>
	constexpr Matrix<1, 1, T> operator+(const Matrix<1, 1, T>& matrix) noexcept
	{
		return matrix;
	}

	template<typename T>
	constexpr Matrix<1, 1, T> operator-(const Matrix<1, 1, T>& matrix) noexcept
	{
		return Matrix<1, 1, T>(
			-matrix.collums[0]);
	}

	using Matrix1x1 = typename Matrix<1, 1, float>;
}