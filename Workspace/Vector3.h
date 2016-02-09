#pragma once

#include <cmath>
#include <cfloat>
#include <assert.h>

#define E_VEC3 Vector3{FLT_EPSILON, FLT_EPSILON, FLT_EPSILON}

namespace JTL
{

	__declspec(align(16)) struct Vector3
	{
		union
		{
			float v[3];
			struct { float x, y, z; };
			Vector2 xy;
		};

		float &operator[](unsigned i) { return v[i]; }

#pragma region BinaryOperators

		Vector3& operator+= (const Vector3 &rhs)
		{
			return *this = Vector3{ x + rhs.x, y + rhs.y, z + rhs.z };
		}

		Vector3& operator-= (const Vector3 &rhs)
		{
			return *this = Vector3{ x - rhs.x, y - rhs.y, z - rhs.z };
		}

		Vector3& operator*= (const float   &rhs)
		{
			return *this = Vector3{ x * rhs, y * rhs, z * rhs };
		}

		Vector3& operator/= (const float   &rhs)
		{
			return *this = Vector3{ x / rhs, y / rhs, z / rhs };
		}


		Vector3  operator+  (const Vector3 &rhs) const
		{
			Vector3 result = *this;
			result += rhs;
			return result;
		}

		Vector3  operator-  (const Vector3 &rhs) const
		{
			Vector3 result = *this;
			result -= rhs;
			return result;
		}

		Vector3  operator*  (const float   &rhs) const
		{
			Vector3 result = *this;
			result *= rhs;
			return result;
		}

		Vector3  operator/  (const float   &rhs) const
		{
			Vector3 result = *this;
			result /= rhs;
			return result;
		}


		bool operator==     (const Vector3 &rhs) const
		{
			return  x == rhs.x && y == rhs.y && z == rhs.z
				||  rhs < *this + E_VEC3 && *this - E_VEC3 < rhs;
		}

		bool operator!=		(const Vector3 &rhs) const
		{
			return !(*this == rhs);
		}

		bool operator<		(const Vector3 &rhs) const
		{
			return x < rhs.x - FLT_EPSILON
				&& y < rhs.y - FLT_EPSILON
				&& z < rhs.z - FLT_EPSILON;
		}

		bool operator>		(const Vector3 &rhs) const
		{
			return x > rhs.x + FLT_EPSILON
				&& y > rhs.y + FLT_EPSILON
				&& z > rhs.z + FLT_EPSILON;
		}

		bool operator<=		(const Vector3 &rhs) const
		{
			return *this == rhs || *this < rhs;
		}

		bool operator>=		(const Vector3 &rhs) const
		{
			return *this == rhs || *this > rhs;
		}

#pragma endregion


#pragma region UnaryOperators

		Vector3& operator-() const
		{
			return Vector3{ -x,-y,-z };
		}

#pragma endregion


		Vector3  normal	   (const Vector3 &v);

		void	 normalize ()
		{
			*this = normal(*this);
		}

	};

#pragma region FunctionHeaders

		float    dot    (const Vector3 &a, const Vector3 &b);

		float    mag    (const Vector3 &v);

		Vector3  normal (const Vector3 &v);

		Vector3  cross  (const Vector3 &a, const Vector3 &b);

		Vector3  lerp   (const Vector3 &a, const Vector3 &b, const float &alpha);

		Vector3  clamp  (const Vector3 &a, const Vector3 &min, const Vector3 &max);

		Vector3  min    (const Vector3 *pts, size_t n);

		Vector3  max    (const Vector3 *pts, size_t n);

#pragma endregion

}