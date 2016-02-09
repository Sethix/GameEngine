#pragma once

#include <cmath>
#include <cfloat>
#include <assert.h>

#define E_VEC2 Vector2{FLT_EPSILON, FLT_EPSILON}

namespace JTL
{

    __declspec(align(16)) struct Vector2
	{
		union
		{
			float v[2];
			struct { float x, y; };
		};

#pragma region BinaryOperators

		Vector2& operator+= (const Vector2 &rhs)
		{
			return *this = Vector2{ x + rhs.x, y + rhs.y };
		}

		Vector2& operator-= (const Vector2 &rhs)
		{
			return *this = Vector2{ x - rhs.x, y - rhs.y };
		}

		Vector2& operator*= (const float   &rhs)
		{
			return *this = Vector2{ x * rhs, y * rhs };
		}

		Vector2& operator/= (const float   &rhs)
		{
			return *this = Vector2{ x / rhs, y / rhs };
		}


		Vector2  operator+  (const Vector2 &rhs) const
		{
			Vector2 result = *this;
			result += rhs;
			return result;
		}

		Vector2  operator-  (const Vector2 &rhs) const
		{
			Vector2 result = *this;
			result -= rhs;
			return result;
		}

		Vector2  operator*  (const float   &rhs) const
		{
			Vector2 result = *this;
			result *= rhs;
			return result;
		}

		Vector2  operator/  (const float   &rhs) const
		{
			Vector2 result = *this;
			result /= rhs;
			return result;
		}


		bool operator==     (const Vector2 &rhs) const
		{
			return x == rhs.x && y == rhs.y
				|| rhs < *this + E_VEC2 && *this - E_VEC2 < rhs;
		}

		bool operator!=     (const Vector2 &rhs) const
		{			
			return !(*this == rhs);
		}

		bool operator<      (const Vector2 &rhs) const
		{
			return x < rhs.x - FLT_EPSILON 
				&& y < rhs.y - FLT_EPSILON;
		}

		bool operator>      (const Vector2 &rhs) const
		{
			return x > rhs.x + FLT_EPSILON 
				&& y > rhs.y + FLT_EPSILON;
		}

		bool operator<=     (const Vector2 &rhs) const
		{
			return *this == rhs || *this < rhs;
		}

		bool operator>=     (const Vector2 &rhs) const
		{
			return *this == rhs || *this > rhs;
		}

#pragma endregion


#pragma region UnaryOperators

		float &operator[](unsigned idx)		  { return v[idx]; }
		float  operator[](unsigned idx) const { return v[idx]; }

		Vector2& operator-() const
		{
			return Vector2{ -x,-y };
		}

#pragma endregion


		Vector2  normal	   (const Vector2 &v);

		void     normalize ()
		{
			*this = normal(*this);
		}

	};

#pragma region FunctionHeaders

	float    dot(const Vector2 &a, const Vector2 &b);

	float    mag(const Vector2 &v);

	float    toAngle(const Vector2 &v);

	Vector2  fromAngle(const float &a);

	Vector2  normal(const Vector2 &v);

	Vector2  lerp(const Vector2 &a, const Vector2 &b, const float &alpha);

	Vector2  clamp(const Vector2 &a, const Vector2 &min, const Vector2 &max);

	Vector2  min(const Vector2 *pts, size_t n);

	Vector2  max(const Vector2 *pts, size_t n);

	Vector2  perp(Vector2 &a);

	Vector2  reflect(const Vector2 &incident, const Vector2 &normal);

#pragma endregion

}
