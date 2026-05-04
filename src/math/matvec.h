#pragma once
#include "mat.h"
#include "vec.h"

template <typename T, size_t R, size_t C>
inline Vec<T, R> operator*(const Mat<T, R, C>& a, const Vec<T, C>& b)
{
	Vec<T, R> result = {};
	for (size_t i = 0; i < R; i++)
		for (size_t k = 0; k < C; k++)
			result[i] += a[k][i] * b[k];
	return result;
}
