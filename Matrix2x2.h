#pragma once
#include "Matrix.h"

#include "Vector2.h"
namespace math
{
	template <typename T>
	struct Matrix<2, 2, T>
	{
		static_assert(CHECK_IS_NUMBER(T));
		static_assert(CHECK_IS_NOT_CV(T));

		using value_type = typename T;
		using type = typename Matrix<2, 2, T>;
		template <typename T2>
		using col_type_template = Vector<2, T2>;
		using col_type = Vector<2, T>;

		[[nodiscard]] FORCE_INLINE static constexpr size_t columnCount() noexcept { return 2; }
		col_type columns[2];

		FORCE_INLINE T* data() noexcept
		{
			return columns[0].data();
		}

		const FORCE_INLINE T* data() const noexcept
		{
			return columns[0].data();
		}

		static const type identify;

		FORCE_INLINE constexpr Matrix() noexcept : columns{}
		{

		}

		/// <summary>
		/// diagonal matrix
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		FORCE_INLINE constexpr explicit Matrix(value_type value) noexcept
			: columns{
			col_type(value, 0),
			col_type(0, value) }
		{
		}

		FORCE_INLINE constexpr Matrix
		(
			value_type x0, value_type y0,
			value_type x1, value_type y1
		) noexcept : columns{
			col_type(x0, x1),
			col_type(y0, y1)}
		{
		}


		FORCE_INLINE constexpr Matrix(const col_type& column0Value, const col_type& column1Value) noexcept
			: columns{ column0Value, column1Value }
		{
		}

		template <typename X, typename Y>
		FORCE_INLINE constexpr Matrix(const col_type_template<X>& column0, const col_type_template<Y>& column1) noexcept
			: columns{ column0, column1 }
		{
		}

		FORCE_INLINE constexpr explicit Matrix(const type& matrix) noexcept
			: columns{ matrix.columns[0], matrix.columns[1] }
		{
		}

		template <typename X>
		FORCE_INLINE constexpr Matrix(const Matrix<1, 1, X>& matrix) noexcept
			: columns{ matrix.columns[0], {0, 1} }
		{
		}

		template <typename X>
		FORCE_INLINE constexpr Matrix(const Matrix<2, 2, X>& matrix) noexcept
			: columns{ matrix.columns[0], matrix.columns[1] }
		{
		}

		template <typename X>
		FORCE_INLINE constexpr Matrix(const Matrix<3, 3, X>& matrix) noexcept
			: columns{ matrix.columns[0], matrix.columns[1] }
		{
		}

		template <typename X>
		FORCE_INLINE constexpr Matrix(const Matrix<4, 4, X>& matrix) noexcept
			: columns{ matrix.columns[0], matrix.columns[1] }
		{
		}

		FORCE_INLINE constexpr type& operator=(value_type value) noexcept
		{
			columns[0] = value;
			columns[1] = value;
			return *this;
		}

		FORCE_INLINE constexpr type& operator=(const col_type& column) noexcept
		{
			columns[0] = column;
			columns[1] = column;
			return *this;
		}

		FORCE_INLINE constexpr type& operator=(const type& matrix) noexcept
		{
			columns[0] = matrix.columns[0];
			columns[1] = matrix.columns[1];
			return *this;
		}

		template <typename X>
		FORCE_INLINE constexpr type& operator=(const Matrix<1, 1, X>& matrix) noexcept
		{
			columns[0] = matrix.columns[0];
			columns[1] = 0;
			return *this;
		}

		template <typename X>
		FORCE_INLINE constexpr type& operator=(const Matrix<2, 2, X>& matrix) noexcept
		{
			columns[0] = matrix.columns[0];
			columns[1] = matrix.columns[1];
			return *this;
		}

		template <typename X>
		FORCE_INLINE constexpr type& operator=(const Matrix<3, 3, X>& matrix) noexcept
		{
			columns[0] = matrix.columns[0];
			columns[1] = matrix.columns[1];
			return *this;
		}

		template <typename X>
		FORCE_INLINE constexpr type& operator=(const Matrix<4, 4, X>& matrix) noexcept
		{
			columns[0] = matrix.columns[0];
			columns[1] = matrix.columns[1];
			return *this;
		}

		// 		Matrix(const type&) = default;
		// 		Matrix(type&&) = default;
		// 		type& opreator=(const type&) = default;
		// 		type& opreator=(type&&) = default;

		std::basic_string<char> toString() const noexcept
		{
			std::stringstream ss;
			ss << columns[0].x << "  " << columns[1].x << '\n';
			ss << columns[0].y << "  " << columns[1].y;
			return ss.str();
		}

		[[nodiscard]] FORCE_INLINE constexpr col_type& operator[](size_t i)
		{
			assert(i >= 0 || i < columnCount());
			return columns[i];
		}

		[[nodiscard]] FORCE_INLINE constexpr const col_type& operator[](size_t i) const
		{
			assert(i >= 0 || i < columnCount());
			return columns[i];
		}



		template <typename X>
		FORCE_INLINE constexpr type operator+(const Matrix<2, 2, X>& rhs) const noexcept
		{
			return type(columns[0] + rhs.columns[0], columns[1] + rhs.columns[1]);
		}

		template <typename X>
		FORCE_INLINE constexpr type operator-(const Matrix<2, 2, X>& rhs) const noexcept
		{
			return type(columns[0] - rhs.columns[0], columns[1] - rhs.columns[1]);
		}

		template <typename X>
		[[nodiscard]] FORCE_INLINE constexpr type operator*(const Matrix<2, 2, X>& rhs) const noexcept
		{
			const col_type SrcA0 = columns[0];
			const col_type SrcA1 = columns[1];

			const col_type SrcB0 = rhs[0];
			const col_type SrcB1 = rhs[1];

			Matrix<2, 2, T> Result;
			Result[0] = SrcA0 * SrcB0[0] + SrcA1 * SrcB0[1];
			Result[1] = SrcA0 * SrcB1[0] + SrcA1 * SrcB1[1];
			return type{ Result };
		}

		template <typename X>
		[[nodiscard]] FORCE_INLINE constexpr Vector<2, X> operator*(const Vector<2, X>& vector) const noexcept
		{
			return  Vector<2, X>
			{
				this->columns[0][0] * vector[0] + this->columns[1][0] * vector[1],
					this->columns[0][1] * vector[0] + this->columns[1][1] * vector[1],
			};
		}

		FORCE_INLINE constexpr type operator+(T rhs) const noexcept
		{
			return type(columns[0] + rhs, columns[1] + rhs);
		}

		FORCE_INLINE constexpr type operator-(T rhs) const noexcept
		{
			return type(columns[0] - rhs, columns[1] - rhs);
		}

		FORCE_INLINE constexpr type operator*(T rhs) const noexcept
		{
			return type(columns[0] * rhs, columns[1] * rhs);
		}

		/*
		template <typename X>
		FORCE_INLINE constexpr type operator/(const Matrix<4, X>& rhs)
		{
			return type(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
		}

		template <typename X>
		FORCE_INLINE constexpr type operator%(const Matrix<4, X>& rhs)
		{
			return type(x % rhs.x, y % rhs.y, z % rhs.z, w % rhs.w);
		}
		*/

		template <typename X>
		FORCE_INLINE constexpr type& operator+=(const Matrix<2, 2, X>& rhs) noexcept
		{
			columns[0] += rhs.columns[0];
			columns[1] += rhs.columns[1];
			return *this;
		}

		template <typename X>
		FORCE_INLINE constexpr type& operator-=(const Matrix<2, 2, X>& rhs) noexcept
		{
			columns[0] -= rhs.columns[0];
			columns[1] -= rhs.columns[1];
			return *this;
		}


		template <typename X>
		FORCE_INLINE constexpr type& operator*=(const Matrix<2, 2, X>& rhs) noexcept
		{
			return (*this = *this * rhs);
		}



		/*
		template <typename X>
		FORCE_INLINE constexpr type& operator/=(const Matrix<4, X>& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			z /= rhs.z;
			w /= rhs.w;
			return *this;
		}

		template <typename X>
		FORCE_INLINE type& operator%=(const Matrix<4, X>& rhs)
		{
			x %= rhs.x;
			y %= rhs.y;
			z %= rhs.z;
			w %= rhs.w;
			return *this;
		}
		*/
		//

		FORCE_INLINE constexpr type& operator+=(T scalar) noexcept
		{
			columns[0] += scalar;
			columns[1] += scalar;
			return *this;
		}

		FORCE_INLINE constexpr type& operator-=(T scalar) noexcept
		{
			columns[0] -= scalar;
			columns[1] -= scalar;
			return *this;
		}

		FORCE_INLINE constexpr type& operator*=(T scalar) noexcept
		{
			columns[0] *= scalar;
			columns[1] *= scalar;
			return *this;
		}

		/*
		template <typename X>
		FORCE_INLINE constexpr type& operator/=(const X& scalar)
		{
			x /= scalar;
			y /= scalar;
			z /= scalar;
			w /= scalar;
			return *this;
		}


		template <typename X, std::enable_if_t<std::is_integral_v<X>, bool> = true>
		FORCE_INLINE type& operator%=(const X& scalar)
		{
			x %= scalar;
			y %= scalar;
			z %= scalar;
			w %= scalar;
			return *this;
		}

		template <typename X, std::enable_if_t<std::is_floating_point_v<X>, bool> = true>
		FORCE_INLINE type& operator%=(const X& scalar)
		{

			x %= std::fmod(x, scalar);
			y %= std::fmod(y, scalar);
			z %= std::fmod(z, scalar);
			w %= std::fmod(w, scalar);
			return *this;
		}
		*/

		//

		[[nodiscard]] FORCE_INLINE constexpr bool operator==(const type& rhs) const noexcept
		{
			return this->columns[0] == rhs.columns[0] && this->columns[1] == rhs.columns[1];
		}

		[[nodiscard]] FORCE_INLINE constexpr bool operator!=(const type& rhs) const noexcept
		{
			return this->columns[0] != rhs.columns[0] || this->columns[1] != rhs.columns[1];
		}

		[[nodiscard]] FORCE_INLINE constexpr bool operator==(T number) const noexcept
		{
			return this->columns[0] == number && this->columns[1] == number;
		}

		[[nodiscard]] FORCE_INLINE constexpr bool operator!=(T number) const noexcept
		{
			return this->columns[0] != number || this->columns[1] != number;
		}

		/// <summary>
		/// prefix
		/// </summary>
		/// <returns></returns>
		FORCE_INLINE constexpr type& operator++() noexcept
		{
			++columns[0];
			++columns[1];
			return *this;
		}

		/// <summary>
		/// postfix
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		FORCE_INLINE constexpr type operator++(int) noexcept
		{
			type Matrix{ *this };
			++* this;
			return Matrix;
		}

		/// <summary>
		/// prefix
		/// </summary>
		/// <returns></returns>
		FORCE_INLINE constexpr type& operator--() noexcept
		{
			--columns[0];
			--columns[1];
			return *this;
		}

		/// <summary>
		/// postfix
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		FORCE_INLINE constexpr type operator--(int) noexcept
		{
			type Matrix{ *this };
			--* this;
			return Matrix;
		}

		operator std::basic_string<char>() const noexcept
		{
			return this->toString();
		}

		template <typename U = T, std::enable_if_t<std::is_signed_v<U>, bool> = true>
		inline constexpr type inverse() const noexcept
		{
			value_type OneOverDetercolumnsinant = static_cast<value_type>(1) / (
				+columns[0][0] * columns[1][1]
				- columns[1][0] * columns[0][1]);

			type Inverse(
				+columns[1][1] * OneOverDetercolumnsinant,
				-columns[0][1] * OneOverDetercolumnsinant,
				-columns[1][0] * OneOverDetercolumnsinant,
				+columns[0][0] * OneOverDetercolumnsinant);

			return Inverse;
		}

		inline constexpr type transpose() const noexcept
		{
			type Result;
			Result[0][0] = columns[0][0];
			Result[0][1] = columns[1][0];
			Result[1][0] = columns[0][1];
			Result[1][1] = columns[1][1];
			return Result;
		}

		inline constexpr value_type determinant() const noexcept
		{
			return columns[0][0] * columns[1][1] - columns[1][0] * columns[0][1];
		}

		inline constexpr auto trace() const noexcept
		{
			return columns[0][0] + columns[1][1];
		}
	};

	template<typename T>
	FORCE_INLINE constexpr Matrix<2, 2, T> operator+(const Matrix<2, 2, T>& matrix) noexcept
	{
		return matrix;
	}

	template<typename T>
	FORCE_INLINE constexpr Matrix<2, 2, T> operator-(const Matrix<2, 2, T>& matrix) noexcept
	{
		return Matrix<2, 2, T>(
			-matrix.columns[0],
			-matrix.columns[1]);
	}

	using Matrix2x2 = typename Matrix<2, 2, float>;

	extern template struct math::Matrix<2, 2, float>;
	extern template struct math::Matrix<2, 2, double>;

}