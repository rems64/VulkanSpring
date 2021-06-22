#pragma once

namespace SE
{
	template <typename T>
	class Vector2
	{
	public:
		Vector2(T x, T y) : x(x), y(y)
		{
		};

		Vector2(const Vector2<T>& left) : x(left.x), y(left.y)
		{
		};

		template <typename U>
		Vector2(const Vector2<U>& left) : x(static_cast<T>(left.x)), y(static_cast<T>(left.y))
		{
		};

		float length() { return sqrt(x * x + y * y); };
		double preciseLength() { return sqrt(x * x + y * y); };
	public:
		T x;
		T y;
	};

	template <typename T>
	inline Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right)
	{
		return Vector2<T>(left.x + right.x, left.y + right.y);
	}

	template <typename T>
	inline Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right)
	{
		return Vector2<T>(left.x - right.x, left.y - right.y);
	}

	template <typename T, typename U>
	inline Vector2<T> operator*(const Vector2<T>& left, const U& right)
	{
		return Vector2<T>(left.x * right, left.y * right);
	}

	template <typename T, typename U>
	inline Vector2<T> operator*(const U& left, const Vector2<T>& right)
	{
		return Vector2<T>(left * right.x, left * right.y);
	}

	template <typename T, typename U>
	inline Vector2<T> operator/(const Vector2<T>& left, const U& right)
	{
		return Vector2<T>(left.x / right, left.y / right);
	}

	template <typename T>
	inline Vector2<T> operator-(const Vector2<T>& right)
	{
		return Vector2<T>(-right.x, -right.y);
	}

	template <typename T>
	inline Vector2<T>& operator +=(Vector2<T>& left, const Vector2<T>& right)
	{
		left.x += right.x;
		left.y += right.y;
		return left;
	}

	template <typename T>
	inline Vector2<T>& operator -=(Vector2<T>& left, const Vector2<T>& right)
	{
		left.x -= right.x;
		left.y -= right.y;
		return left;
	}

	template <typename T>
	inline bool operator==(const Vector2<T>& left, const Vector2<T>& right)
	{
		return (left.x == right.x) && (left.y == right.y);
	}

	template <typename T>
	inline bool operator!=(const Vector2<T>& left, const Vector2<T>& right)
	{
		return (left.x != right.x) || (left.y != right.y);
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& os, Vector2<T> vector) {
		return os << "(x:" << vector.x << ", y:" << vector.y << ")";
	}

	typedef Vector2<float> Vector2f;

	typedef Vector2<int> Vector2i;
	typedef Vector2<unsigned int> Vector2ui;

	typedef Vector2<long> Vector2l;
	typedef Vector2<unsigned long> Vector2ul;
}