#include "Vector3.h"

namespace JTL
{
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
		return Vector3{ a.x + ((a.x - b.x) * alpha) ,
			a.y + ((a.y - b.y) * alpha) ,
			a.z + ((a.z - b.z) * alpha) };
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


	void	 DebugV3()
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