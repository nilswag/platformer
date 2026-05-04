#pragma once

template<typename T, int N>
struct Vec {
	T data[N];

	inline T& operator[](int i) { return data[i]; }

	inline const T& operator[](int i) const { return data[i]; }

	inline Vec<T, N> operator+(const Vec<T, N>& other) const
	{
		Vec<T, N> result;
		for (int i = 0; i < N; i++)
			result.data[i] = data[i] + other.data[i];
		return result;
	}

	inline Vec<T, N> operator+=(const Vec<T, N>& other)
	{
		for (int i = 0; i < N; i++)
			data[i] += other.data[i];
	}
};

using Vec2 = Vec<int, 2>;
using Vec3 = Vec<int, 3>;
using Vec4 = Vec<int, 4>;

using Vec2f = Vec<float, 2>;
using Vec3f = Vec<float, 3>;
using Vec4f = Vec<float, 4>;