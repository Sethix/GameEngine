#include <cassert>
#include <cfloat>
#include <cmath>
#include "Vector2.h"

namespace JTL
{
#pragma region BinaryOperators

	Vector2& Vector2::operator+= (const Vector2 &rhs)
	{
		return *this = Vector2{ x + rhs.x, y + rhs.y };
	}

	Vector2& Vector2::operator-= (const Vector2 &rhs)
	{
		return *this = Vector2{ x - rhs.x, y - rhs.y };
	}

	Vector2& Vector2::operator*= (const float   &rhs)
	{
		return *this = Vector2{ x * rhs, y * rhs };
	}

	Vector2& Vector2::operator/= (const float   &rhs)
	{
		return *this = Vector2{ x / rhs, y / rhs };
	}


	Vector2  Vector2::operator+  (const Vector2 &rhs) const
	{
		Vector2 result = *this;
		result += rhs;
		return result;
	}

	Vector2  Vector2::operator-  (const Vector2 &rhs) const
	{
		Vector2 result = *this;
		result -= rhs;
		return result;
	}

	Vector2  Vector2::operator*  (const float   &rhs) const
	{
		Vector2 result = *this;
		result *= rhs;
		return result;
	}

	Vector2  Vector2::operator/  (const float   &rhs) const
	{
		Vector2 result = *this;
		result /= rhs;
		return result;
	}


	bool Vector2::operator==     (const Vector2 &rhs) const
	{
		return x == rhs.x && y == rhs.y
			|| rhs < *this + E_VEC2 && *this - E_VEC2 < rhs;
	}

	bool Vector2::operator!=     (const Vector2 &rhs) const
	{
		return !(*this == rhs);
	}

	bool Vector2::operator<      (const Vector2 &rhs) const
	{
		return x < rhs.x - FLT_EPSILON
			&& y < rhs.y - FLT_EPSILON;
	}

	bool Vector2::operator>      (const Vector2 &rhs) const
	{
		return x > rhs.x + FLT_EPSILON
			&& y > rhs.y + FLT_EPSILON;
	}

	bool Vector2::operator<=     (const Vector2 &rhs) const
	{
		return *this == rhs || *this < rhs;
	}

	bool Vector2::operator>=     (const Vector2 &rhs) const
	{
		return *this == rhs || *this > rhs;
	}

#pragma endregion

#pragma region UnaryOperators

	float   &Vector2::operator[](unsigned idx)		 { return v[idx]; }

	float    Vector2::operator[](unsigned idx) const { return v[idx]; }


	Vector2& Vector2::operator-() const
	{
		return Vector2{ -x,-y };
	}

#pragma endregion

#pragma region VectorFunctions

	void     Vector2::normalize()
	{
		*this = normal(*this);
	}

	float    dot		(const Vector2 &a  , const Vector2 &b)
	{
		return a.x * b.x + a.y * b.y;
	}

	float    mag		(const Vector2 &v)
	{
		return sqrtf(pow(v.x, 2) + pow(v.y, 2));
	}

	float    toAngle	(const Vector2 &v)
	{
		return atan2f(v.y, v.x);
	}

	Vector2  fromAngle  (const float   &a)
	{
		return Vector2{ cosf(a), sinf(a) };
	}

	Vector2  normal		(const Vector2 &v)
	{
		float m = mag(v);
		return Vector2{ v.x / m, v.y / m };
	}

	Vector2  lerp		(const Vector2 &a  , const Vector2 &b  , const float   &alpha)
	{
		return Vector2{ a.x + ((a.x - b.x) * alpha) ,
			a.y + ((a.y - b.y) * alpha) };
	}

	Vector2  clamp		(const Vector2 &a  , const Vector2 &min, const Vector2 &max  )
	{
		Vector2 r = a;

		if (a.x < min.x) r.x = min.x;
		else if (a.x > max.x) r.x = max.x;

		if (a.y < min.y) r.y = min.y;
		else if (a.y > max.y) r.y = max.y;

		return r;
	}

	Vector2  min		(const Vector2 *pts, size_t n)
	{
		Vector2 temp = pts[0];

		for (size_t i = 1; i < n; ++i)
		{
			if (pts[i].x < temp.x) temp.x = pts[i].x;
			if (pts[i].y < temp.y) temp.y = pts[i].y;
		}

		return temp;
	}

	Vector2  max		(const Vector2 *pts, size_t n)
	{
		Vector2 temp = pts[0];

		for (size_t i = 1; i < n; ++i)
		{
			if (pts[i].x > temp.x) temp.x = pts[i].x;
			if (pts[i].y > temp.y) temp.y = pts[i].y;
		}

		return temp;
	}

	Vector2  perp		(Vector2 &a)
	{
		return{ -a.y, a.x };
	}

	Vector2  reflect	(const Vector2 &incident, const Vector2 &normal)
	{
		return incident - (normal * (2 * dot(incident, normal)));
	}

#pragma endregion

	void	 DebugV2()
	{

		Vector2 a{ 1, 1 };
		Vector2 b{ 2, 3 };

		Vector2 t;


		t = a + b;

		assert(t.x == 3 && t.y == 4);


		t = a - b;

		assert(t.x == -1 && t.y == -2);


		t = a * 5;

		assert(t.x == 5 && t.y == 5);


		t = b / 2;

		assert(t.x == 1 && t.y == 1.5);


		assert(mag(Vector2{ 2, 2 }) == 2.82842708f);


		t = normal(b);

		assert(mag(t) == 1);


		assert(dot(a, b) == 5);

		//t = Vector2{ 1.5f, 2 };

		//assert(lerp(a, b, 0.5f) == Vector2{ 2,2 });

	}
}