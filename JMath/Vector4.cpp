#include <cassert>
#include <cfloat>
#include <cmath>
#include "Vector4.h"

namespace JTL
{
#pragma region BinaryOperators

	Vector4& Vector4::operator+= (const Vector4 &rhs)
	{
		return *this = Vector4{ x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w };
	}

	Vector4& Vector4::operator-= (const Vector4 &rhs)
	{
		return *this = Vector4{ x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w };
	}

	Vector4& Vector4::operator*= (const float   &rhs)
	{
		return *this = Vector4{ x * rhs, y * rhs, z * rhs, w * rhs };
	}

	Vector4& Vector4::operator/= (const float   &rhs)
	{
		return *this = Vector4{ x / rhs, y / rhs, z / rhs, w / rhs };
	}


	Vector4  Vector4::operator+  (const Vector4 &rhs) const
	{
		Vector4 result = *this;
		result += rhs;
		return result;
	}

	Vector4  Vector4::operator-  (const Vector4 &rhs) const
	{
		Vector4 result = *this;
		result -= rhs;
		return result;
	}

	Vector4  Vector4::operator*  (const float   &rhs) const
	{
		Vector4 result = *this;
		result *= rhs;
		return result;
	}

	Vector4  Vector4::operator/  (const float   &rhs) const
	{
		Vector4 result = *this;
		result /= rhs;
		return result;
	}


	bool Vector4::operator==	 (const Vector4 &rhs) const
	{
		return (x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w)
			|| (rhs < *this + E_VEC4 && *this - E_VEC4 < rhs);
	}

	bool Vector4::operator!=	 (const Vector4 &rhs) const
	{
		return !(*this == rhs);
	}

	bool Vector4::operator<		 (const Vector4 &rhs) const
	{
		return x < rhs.x - FLT_EPSILON
			&& y < rhs.y - FLT_EPSILON
			&& z < rhs.z - FLT_EPSILON
			&& w < rhs.w - FLT_EPSILON;
	}

	bool Vector4::operator>		 (const Vector4 &rhs) const
	{
		return x > rhs.x + FLT_EPSILON
			&& y > rhs.y + FLT_EPSILON
			&& z > rhs.z + FLT_EPSILON
			&& w > rhs.w + FLT_EPSILON;
	}

	bool Vector4::operator<=	 (const Vector4 &rhs) const
	{
		return *this == rhs || *this < rhs;
	}

	bool Vector4::operator>=	 (const Vector4 &rhs) const
	{
		return *this == rhs || *this > rhs;
	}

#pragma endregion

#pragma region UnaryOperators

	float& Vector4::operator[](unsigned i)		 { return v[i]; };

	float  Vector4::operator[](unsigned i) const { return v[i]; };


	Vector4  Vector4::operator-() const
	{
		return Vector4{ -x,-y,-z,-w };
	}

#pragma endregion

#pragma region VectorFunctions

	void Vector4::normalize()
	{
		*this = normal(*this);
	}

	float    dot	(const Vector4 &a  , const Vector4 &b)
	{
	
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	float    mag	(const Vector4 &v)
	{
		return sqrtf(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2) + pow(v.w, 2));
	}

	Vector4  normal (const Vector4 &v)
	{
		float m = mag(v);
		return Vector4{ v.x / m, v.y / m, v.z / m, v.w / m };
	}

	Vector4  lerp	(const Vector4 &a  , const Vector4 &b  , const float   &alpha)
	{
		return Vector4{ a.x + ((a.x - b.x) * alpha) ,
			a.y + ((a.y - b.y) * alpha) ,
			a.z + ((a.z - b.z) * alpha) ,
			a.w + ((a.w - b.w) * alpha) };
	}

	Vector4  clamp	(const Vector4 &a  , const Vector4 &min, const Vector4 &max  )
	{
		Vector4 r = a;

		if (a.x < min.x) r.x = min.x;
		else if (a.x > max.x) r.x = max.x;

		if (a.y < min.y) r.y = min.y;
		else if (a.y > max.y) r.y = max.y;

		if (a.z < min.z) r.z = min.z;
		else if (a.z > max.z) r.z = max.z;

		if (a.w < min.w) r.w = min.w;
		else if (a.w > max.w) r.w = max.w;

		return r;
	}

	Vector4  min	(const Vector4 *pts, size_t n)
	{
		Vector4 temp = pts[0];

		for (size_t i = 1; i < n; ++i)
		{
			if (pts[i].x < temp.x) temp.x = pts[i].x;
			if (pts[i].y < temp.y) temp.y = pts[i].y;
			if (pts[i].z < temp.z) temp.z = pts[i].z;
			if (pts[i].w < temp.w) temp.w = pts[i].w;
		}

		return temp;
	}

	Vector4  max	(const Vector4 *pts, size_t n)
	{
		Vector4 temp = pts[0];

		for (size_t i = 1; i < n; ++i)
		{
			if (pts[i].x > temp.x) temp.x = pts[i].x;
			if (pts[i].y > temp.y) temp.y = pts[i].y;
			if (pts[i].z > temp.z) temp.z = pts[i].z;
			if (pts[i].w > temp.w) temp.w = pts[i].w;
		}

		return temp;
	}

#pragma endregion

	void	 DebugV4()
	{

		Vector4 a{ 1, 1, 1, 1 };
		Vector4 b{ 2, 3, 4, 5 };

		Vector4 t;


		t = a + b;

		assert(t.x == 3 && t.y == 4 && t.z == 5 && t.w == 6);


		t = a - b;

		assert(t.x == -1 && t.y == -2 && t.z == -3 && t.w == -4);


		t = a * 5;

		assert(t.x == 5 && t.y == 5 && t.z == 5 && t.w == 5);


		t = b / 2;

		assert(t.x == 1 && t.y == 1.5 && t.z == 2 && t.w == 2.5);


		assert(mag(Vector4{ 2, 2, 2, 2 }) == 4);


		t = normal(b);

		assert(mag(t) == 1);


		assert(dot(a, b) == 14);

	}
}