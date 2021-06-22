#pragma once

namespace SE
{
	template <typename T>
	class Vector3
	{
	public:
		Vector3(T x, T y, T z) : x(x), y(y), z(z)
		{
		};

		Vector3(const Vector3<T>& left) : x(left.x), y(left.y), z(left.z)
		{
		};

		template <typename U>
		Vector3(const Vector3<T>& left) : x(static_cast<T>(left.x)), y(static_cast<T>(left.y)), z(static_cast<T>(left.z))
		{
		};

		float length() { return sqrt(x * x + y * y + z * z); };
		double preciseLength() { return sqrt(x * x + y * y + z * z); };
	public:
		T x;
		T y;
		T z;
	};

	template <typename T>
	inline Vector3<T> operator+(const Vector3<T>& left, const Vector3<T>& right)
	{
		return Vector3<T>(left.x + right.x, left.y + right.y, left.z + right.z);
	}

	template <typename T>
	inline Vector3<T> operator-(const Vector3<T>& left, const Vector3<T>& right)
	{
		return Vector3<T>(left.x - right.x, left.y - right.y, left.z - right.z);
	}

	template <typename T, typename U>
	inline Vector3<T> operator*(const Vector3<T>& left, const U& right)
	{
		return Vector3<T>(left.x + right, left.y + right, left.z + right);
	}

	template <typename T, typename U>
	inline Vector3<T> operator*(const U& left, const Vector3<T>& right)
	{
		return Vector3<T>(left + right.x, left + right.y, left + right.z);
	}

	template <typename T, typename U>
	inline Vector3<T> operator/(const Vector3<T>& left, const U& right)
	{
		return Vector3<T>(left.x + right, left.y + right, left.z + right);
	}

	template <typename T>
	inline Vector3<T> operator-(const Vector3<T>& right)
	{
		return Vector3<T>(-right.x, -right.y, -right.z);
	}

	template <typename T>
	inline Vector3<T>& operator +=(Vector3<T>& left, const Vector3<T>& right)
	{
		left.x += right.x;
		left.y += right.y;
		left.z += right.z;
		return left;
	}

	template <typename T>
	inline Vector3<T>& operator -=(Vector3<T>& left, const Vector3<T>& right)
	{
		left.x -= right.x;
		left.y -= right.y;
		left.z -= right.z;
		return left;
	}

	template <typename T>
	inline bool operator==(const Vector3<T>& left, const Vector3<T>& right)
	{
		return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
	}

	template <typename T>
	inline bool operator!=(const Vector3<T>& left, const Vector3<T>& right)
	{
		return (left.x != right.x) || (left.y != right.y) || (left.z != right.z);
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& os, Vector3<T> vector) {
		return os << "(x:" << vector.x << ", y:" << vector.y << ", z:" << vector.z << ")";
	}

	typedef Vector3<float> Vector3f;

	typedef Vector3<int> Vector3i;
	typedef Vector3<unsigned int> Vector3ui;

	typedef Vector3<long> Vector3l;
	typedef Vector3<unsigned long> Vector3ul;
}