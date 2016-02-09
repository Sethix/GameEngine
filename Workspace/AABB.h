#pragma once

#include "Vector2.h"
#include "Transform.h"

namespace JTL
{

	struct AABB2D
	{
	private:
		Vector2* pts[4];
	
	public:
		AABB2D(const Vector2 &a, const Vector2 &b)
		{
			min = a;
			max = b;
		}

		Vector2 min, max;

		Vector2 dim() const
		{
			return max - min;
		}

		Vector2 pos() const
		{
			return (max + min) / 2;
		}

		Vector2* points()
		{
			*pts[0] = { max.x, min.y };
			*pts[1] = max;
			*pts[2] = { min.x, max.y };
			*pts[3] = min;
			return *pts;
		}

	};

	AABB2D operator*(const Matrix3 &m, const AABB2D &a)
	{
		Vector2 omin = a.min;
		Vector2 omax = a.max;

		Vector2 rmin = m[2].xy;
		Vector2 rmax = m[2].xy;

		float p, q;

		for (unsigned j = 0; j < 2; ++j)
			for (unsigned i = 0; i < 2; ++i)
			{
				p = omin[i] * m[i][j];
				q = omax[i] * m[i][j];

				if (p < q) std::swap(p, q);
				rmin[j] += p;
				rmax[j] += q;
			}
		return{ rmin, rmax };
	}

	AABB2D genAABB2D(Vector2 *pts, size_t n)
	{
		return AABB2D(min(pts, n),max(pts, n));
	}

	AABB2D rotate(AABB2D x, float a)
	{
		Vector2 j = Vector2{ x.min.y * sin(a) + x.min.x * cos(a),
							 x.min.x * sin(a) + x.min.y * cos(a) };

		Vector2 k = Vector2{ x.max.y * sin(a) + x.max.x * cos(a),
							 x.max.x * sin(a) + x.max.y * cos(a) };

		Vector2 l[2]{ j, k };

		return genAABB(l, 2);
	}

	bool iTest(const AABB2D &ac, const AABB2D &bc)
	{
		return (ac.pos() - bc.pos()) <= ((ac.dim() / 2) + (bc.dim() / 2));
	}

}