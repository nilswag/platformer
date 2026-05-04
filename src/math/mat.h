#pragma once
#include <type_traits>
#include "vec.h"

template <typename T, size_t R, size_t C>
struct Mat
{
	Vec<T, R> data[C];

	inline Vec<T, R>& operator[](size_t i) { return data[i]; }

	inline const Vec<T, R>& operator[](size_t i) const { return data[i]; }

	inline Mat<T, R, C>& operator+=(const Mat<T, R, C>& other)
	{
		for (size_t i = 0; i < C; i++)
			data[i] += other[i];
		return *this;
	}

	template<typename X>
	inline Mat<T, R, C>& operator*=(const X& x)
	{
		for (size_t i = 0; i < C; i++)
			data[i] *= x;
		return *this;
	}

	static inline Mat<T, C, R> identity()
	{
		Mat<T, C, R> result = {};
		for (size_t i = 0; i < C; i++)
			for (size_t j = 0; j < R; j++)
				result[i][j] = (i == j);
		return result;
	}
};

using Mat2 = Mat<int, 2, 2>;
using Mat3 = Mat<int, 3, 3>;
using Mat4 = Mat<int, 4, 4>;

using Mat2f = Mat<float, 2, 2>;
using Mat3f = Mat<float, 3, 3>;
using Mat4f = Mat<float, 4, 4>;

template<typename T, size_t R, size_t C>
inline Mat<T, R, C> operator+(const Mat<T, R, C>& a, const Mat<T, R, C>& b)
{
	Mat<T, R, C> result = {};
	result += a;
	result += b;
	return result;
}

template <typename T, size_t R1, size_t C1, size_t C2>
inline Mat<T, R1, C2> operator*(const Mat<T, R1, C1>& a, const Mat<T, C1, C2>& b)
{
	Mat<T, R1, C2> result = {};
	for (size_t i = 0; i < C2; i++)
		for (size_t j = 0; j < R1; j++)
			for (size_t k = 0; k < C1; k++)
				result[i][j] += a[k][j] * b[i][k];
	return result;
}
	
template <typename T, size_t R, size_t C, typename X>
inline Mat<T, R, C> operator*(const Mat<T, R, C>& a, const X& x)
{
	Mat<T, R, C> result = a;
	result *= x;
	return result;
}
