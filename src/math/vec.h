#pragma once

template<typename T, size_t N>
struct Vec {
	T data[N];

	inline T& operator[](size_t i) { return data[i]; }

	inline const T& operator[](size_t i) const { return data[i]; }

	inline Vec<T, N>& operator+=(const Vec<T, N>& other)
	{
		for (size_t i = 0; i < N; i++)
			data[i] += other.data[i];
		return *this;
	}
};

template<typename T, size_t N>
inline Vec<T, N> operator+(const Vec<T, N>& a, const Vec<T, N>& b)
{
	Vec<T, N> result = {};
	result += a;
	result += b;
	return result;
}

template<typename T, size_t N>
T dot(const Vec<T, N>& a, const Vec<T, N>& b)
{
	T result = {};
	for (size_t i = 0; i < N; i++)
		result += a[i] * b[i];
	return result;
}

using Vec2 = Vec<int, 2>;
using Vec3 = Vec<int, 3>;
using Vec4 = Vec<int, 4>;

using Vec2f = Vec<float, 2>;
using Vec3f = Vec<float, 3>;
using Vec4f = Vec<float, 4>;