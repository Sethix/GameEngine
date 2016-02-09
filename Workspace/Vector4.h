#pragma once

#include "Vector3.h"

#include <cmath>
#include <cfloat>
#include <assert.h>

#define E_VEC4 Vector4{FLT_EPSILON, FLT_EPSILON, FLT_EPSILON, FLT_EPSILON}

namespace JTL
{

	__declspec(align(32)) struct Vector4
	{
		union
		{
			float v[4];
			struct { float x, y, z, w; };
			struct { float r, g, b, a; };
			struct { Vector3 vector3;  };
		};

#pragma region BinaryOperators

		Vector4& operator+= (const Vector4 &rhs)
		{
			return *this = Vector4{ x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w };
		}

		Vector4& operator-= (const Vector4 &rhs)
		{
			return *this = Vector4{ x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w };
		}

		Vector4& operator*= (const float   &rhs)
		{
			return *this = Vector4{ x * rhs, y * rhs, z * rhs, w * rhs };
		}

		Vector4& operator/= (const float   &rhs)
		{
			return *this = Vector4{ x / rhs, y / rhs, z / rhs, w / rhs };
		}


		Vector4  operator+  (const Vector4 &rhs) const
		{
			Vector4 result = *this;
			result += rhs;
			return result;
		}

		Vector4  operator-  (const Vector4 &rhs) const
		{
			Vector4 result = *this;
			result -= rhs;
			return result;
		}

		Vector4  operator*  (const float   &rhs) const
		{
			Vector4 result = *this;
			result *= rhs;
			return result;
		}

		Vector4  operator/  (const float   &rhs) const
		{
			Vector4 result = *this;
			result /= rhs;
			return result;
		}


		bool operator==     (const Vector4 &rhs) const
		{
			return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w)
				|| (rhs < *this + E_VEC4 && *this - E_VEC4 < rhs);
		}

		bool operator!=		(const Vector4 &rhs) const
		{
			return !(*this == rhs);
		}

		bool operator<		(const Vector4 &rhs) const
		{
			return x < rhs.x - FLT_EPSILON 
				&& y < rhs.y - FLT_EPSILON 
				&& z < rhs.z - FLT_EPSILON 
				&& w < rhs.w - FLT_EPSILON;
		}

		bool operator>		(const Vector4 &rhs) const
		{
			return x > rhs.x + FLT_EPSILON
				&& y > rhs.y + FLT_EPSILON
				&& z > rhs.z + FLT_EPSILON
				&& w > rhs.w + FLT_EPSILON;
		}

		bool operator<=		(const Vector4 &rhs) const
		{
			return *this == rhs || *this < rhs;
		}

		bool operator>=		(const Vector4 &rhs) const
		{
			return *this == rhs || *this > rhs;
		}

#pragma endregion


#pragma region UnaryOperators

		Vector4& operator-() const
		{
			return Vector4{ -x,-y,-z,-w };
		}

#pragma endregion


		Vector4  normal    (const Vector4 &v);

		void     normalize ()
		{
			*this = normal(*this);
		}

	};

#pragma region FunctionHeaders

		float    dot    (const Vector4 &a, const Vector4 &b);

		float    mag    (const Vector4 &v);

		Vector4  normal (const Vector4 &v);

		Vector4  lerp   (const Vector4 &a, const Vector4 &b, const float &alpha);

		Vector4  clamp  (const Vector4 &a, const Vector4 &min, const Vector4 &max);

		Vector4  min    (const Vector4 *pts, size_t n);

		Vector4  max    (const Vector4 *pts, size_t n);

#pragma endregion

}
