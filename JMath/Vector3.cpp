#include <cassert>
#include <cfloat>
#include <cmath>
#include "Vector3.h"

namespace JTL
{
#pragma region BinaryOperators

	Vector3& Vector3::operator+= (const Vector3 &rhs)
	{
		return *this = Vector3{ x + rhs.x, y + rhs.y, z + rhs.z };
	}

	Vector3& Vector3::operator-= (const Vector3 &rhs)
	{
		return *this = Vector3{ x - rhs.x, y - rhs.y, z - rhs.z };
	}

	Vector3& Vector3::operator*= (const float   &rhs)
	{
		return *this = Vector3{ x * rhs, y * rhs, z * rhs };
	}

	Vector3& Vector3::operator/= (const float   &rhs)
	{
		return *this = Vector3{ x / rhs, y / rhs, z / rhs };
	}


	Vector3  Vector3::operator+  (const Vector3 &rhs) const
	{
		Vector3 result = *this;
		result += rhs;
		return result;
	}

	Vector3  Vector3::operator-  (const Vector3 &rhs) const
	{
		Vector3 result = *this;
		result -= rhs;
		return result;
	}

	Vector3  Vector3::operator*  (const float   &rhs) const
	{
		Vector3 result = *this;
		result *= rhs;
		return result;
	}

	Vector3  Vector3::operator/  (const float   &rhs) const
	{
		Vector3 result = *this;
		result /= rhs;
		return result;
	}


	bool Vector3::operator==     (const Vector3 &rhs) const
	{
		return  x == rhs.x && y == rhs.y && z == rhs.z
			|| rhs < *this + E_VEC3 && *this - E_VEC3 < rhs;
	}

	bool Vector3::operator!=	 (const Vector3 &rhs) const
	{
		return !(*this == rhs);
	}

	bool Vector3::operator<		 (const Vector3 &rhs) const
	{
		return x < rhs.x - FLT_EPSILON
			&& y < rhs.y - FLT_EPSILON
			&& z < rhs.z - FLT_EPSILON;
	}

	bool Vector3::operator>		 (const Vector3 &rhs) const
	{
		return x > rhs.x + FLT_EPSILON
			&& y > rhs.y + FLT_EPSILON
			&& z > rhs.z + FLT_EPSILON;
	}

	bool Vector3::operator<=		(const Vector3 &rhs) const
	{
		return *this == rhs || *this < rhs;
	}

	bool Vector3::operator>=		(const Vector3 &rhs) const
	{
		return *this == rhs || *this > rhs;
	}

#pragma endregion

#pragma region UnaryOperators

	float&  Vector3::operator[](unsigned i)		  { return v[i]; }

	float   Vector3::operator[](unsigned i) const { return v[i]; }


	Vector3  Vector3::operator-() const
	{
		return Vector3{ -x,-y,-z };
	}

#pragma endregion

#pragma region VectorFunctions

	void Vector3::normalize()
	{
		*this = normal(*this);
	}

	float    dot	(const Vector3 &a  , const Vector3 &b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	float    mag	(const Vector3 &v)
	{
		return sqrtf(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
	}

	Vector3  normal (const Vector3 &v)
	{
		float m = mag(v);
		return Vector3{ v.x / m, v.y / m, v.z / m };
	}

	Vector3  cross	(const Vector3 &a  , const Vector3 &b)
	{
		return Vector3{ a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x };
	}

	Vector3  lerp	(const Vector3 &a  , const Vector3 &b  , const float   &alpha)
	{
		return Vector3{ a.x + (b.x - a.x) * alpha ,
						a.y + (b.y - a.y) * alpha ,
						a.z + (b.z - a.z) * alpha };
	}

	Vector3  clamp	(const Vector3 &a  , const Vector3 &min, const Vector3 &max  )
	{
		Vector3 r = a;

		if (a.x < min.x) r.x = min.x;
		else if (a.x > max.x) r.x = max.x;

		if (a.y < min.y) r.y = min.y;
		else if (a.y > max.y) r.y = max.y;

		if (a.z < min.z) r.z = min.z;
		else if (a.z > max.z) r.z = max.z;

		return r;
	}

	Vector3  min	(const Vector3 *pts, size_t n)
	{
		Vector3 temp = pts[0];

		for (size_t i = 1; i < n; ++i)
		{
			if (pts[i].x < temp.x) temp.x = pts[i].x;
			if (pts[i].y < temp.y) temp.y = pts[i].y;
			if (pts[i].z < temp.z) temp.z = pts[i].z;
		}

		return temp;
	}

	Vector3  max	(const Vector3 *pts, size_t n)
	{
		Vector3 temp = pts[0];

		for (size_t i = 1; i < n; ++i)
		{
			if (pts[i].x > temp.x) temp.x = pts[i].x;
			if (pts[i].y > temp.y) temp.y = pts[i].y;
			if (pts[i].z > temp.z) temp.z = pts[i].z;
		}

		return temp;
	}

	Vector3  reflect(const Vector3 &incident, const Vector3 &normal)
	{
		return incident - (normal * (2 * dot(incident, normal)));
	}

#pragma endregion

	void DebugV3()
	{

		Vector3 a{ 1, 1, 1 };
		Vector3 b{ 2, 3, 4 };

		Vector3 t;


		t = a + b;

		assert(t.x == 3 && t.y == 4 && t.z == 5);


		t = a - b;

		assert(t.x == -1 && t.y == -2 && t.z == -3);


		t = a * 5;

		assert(t.x == 5 && t.y == 5 && t.z == 5);


		t = b / 2;

		assert(t.x == 1 && t.y == 1.5 && t.z == 2);


		assert(mag(Vector3{ 2, 2, 2 }) == 3.46410155f);


		t = normal(b);

		assert(mag(t) == 1);


		assert(dot(a, b) == 9);


		t = Vector3{ 1,-2,1 };

		assert(cross(a, b) == t);

	}
}