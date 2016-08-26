// TODO : Clean-up and move to math library as it's more fitting

#include <cassert>
#include <algorithm>
#include "AABB2D.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix3.h"
#include "Circle.h"
#include "Plane2D.h"
#include "Ray2D.h"
#include "ConvexHull2D.h"
#include "JMath.h"

namespace JTL
{
	Vector2 AABB2D::dim() const { return max - min; }

	Vector2 AABB2D::pos() const { return (max + min) / 2; }

#pragma region ShapeFunctions

	AABB2D	operator*	(const Matrix3 &m, const AABB2D &a)
	{
		Vector2 omin = a.min;
		Vector2 omax = a.max;

		Vector2 rmin = { m.mm[0][2], m.mm[1][2] };
		Vector2 rmax = { m.mm[0][2], m.mm[1][2] };

		float p, q;

		for (unsigned j = 0; j < 2; ++j)
			for (unsigned i = 0; i < 2; ++i)
			{
				p = omin[i] * m[j][i];
				q = omax[i] * m[j][i];

				if (p > q) std::swap(p, q);
				rmin[j] += p;
				rmax[j] += q;
			}
		return{ rmin, rmax };
	}

	AABB2D	genAABB2D	(const Vector2 *pts, const size_t &n)
	{
		return AABB2D(min(pts, n), max(pts, n));
	}

	AABB2D	rotate		(const AABB2D &x, const float &a)
	{
		Vector2 j = Vector2{ x.min.y * sin(a) + x.min.x * cos(a),
			x.min.x * sin(a) + x.min.y * cos(a) };

		Vector2 k = Vector2{ x.max.y * sin(a) + x.max.x * cos(a),
			x.max.x * sin(a) + x.max.y * cos(a) };

		Vector2 l[2]{ j, k };

		return genAABB2D(l, 2);
	}

#pragma endregion

#pragma region CollisionFunctions

	bool	iTest		(const AABB2D &ac, const AABB2D &bc)
	{
		return !(ac.max.x < bc.min.x || bc.max.x < ac.min.x 
			||   ac.max.y < bc.min.y || bc.max.y < ac.min.y);
	}

	bool	iTest		(const AABB2D &ac, const Circle &bc)
	{
		return iTest(Circle{ clamp(bc.position, ac.min, ac.max) , 0 }, bc);
	}

	bool	iTest		(const AABB2D &ac, const Plane2D &bc)
	{
		return dot(bc.normal, (ac.pos() - bc.position)) <= 
				  (ac.dim().x / 2) * dot(bc.normal, Vector2{ 1,0 }) 
				+ (ac.dim().y / 2) * dot(bc.normal, Vector2{ 0,1 });
	}

	bool	iTest		(const AABB2D &ac, const Ray2D &bc)
	{
		assert(bc.direction[0] + bc.direction[1] != 0);

		Ray2D ray = bc;

		for (int i = 0; i < 2; ++i)
			ray.direction[i] = (ray.direction[i] == 0) ? FLT_EPSILON : ray.direction[i];

		Plane2D planes[4];

		planes[0] = { Vector2{ ac.min.x  , ac.pos().y },Vector2{ -1, 0 } };
		planes[1] = { Vector2{ ac.pos().x, ac.min.y   },Vector2{  0,-1 } };
		planes[2] = { Vector2{ ac.max.x  , ac.pos().y },Vector2{  1, 0 } };
		planes[3] = { Vector2{ ac.pos().x, ac.max.y   },Vector2{  0, 1 } };

		float dists[4];

		float tmin = FLT_MAX;
		float tmax = -FLT_MAX;

		for (int i = 0; i < 4; ++i)
		{
			float deno = -(dot(planes[i].normal, ray.direction));

			dists[i] = dot(planes[i].normal, (ray.position - planes[i].position)) / deno;
		}

		tmin = fmaxf(fminf(dists[0], dists[2]), fminf(dists[1], dists[3]));
		tmax = fminf(fmaxf(dists[0], dists[2]), fmaxf(dists[1], dists[3]));

		return tmin <= tmax && 0 <= tmin <= bc.length;
	}

	CollisionData iTest_data(const AABB2D &ac, const AABB2D &bc)
	{
		if (iTest(ac, bc))
		{
			ConvexHull2D a, b;

			a.size = 4;
			b.size = 4;

			a.verts[0] = Vector2{ ac.min.x, ac.min.y };
			a.verts[1] = Vector2{ ac.min.x, ac.max.y };
			a.verts[2] = Vector2{ ac.max.x, ac.max.y };
			a.verts[3] = Vector2{ ac.max.x, ac.min.y };

			b.verts[0] = Vector2{ bc.min.x, bc.min.y };
			b.verts[1] = Vector2{ bc.min.x, bc.max.y };
			b.verts[2] = Vector2{ bc.max.x, bc.max.y };
			b.verts[3] = Vector2{ bc.max.x, bc.min.y };

			return iTest_data(a, b);
		}
		else return CollisionData{ 0,0 };
	}

	CollisionData iTest_data(const AABB2D &ac, const Circle &bc)
	{
		if (iTest(ac, bc))
		{
			ConvexHull2D a;

			a.size = 4;

			a.verts[2] = ac.min;
			a.verts[1] = Vector2{ ac.min.x, ac.max.y };
			a.verts[0] = ac.max;
			a.verts[3] = Vector2{ ac.max.y, ac.min.y };

			return iTest_data(a, bc);
		}
		else return CollisionData{ 0,0 };
	}

	CollisionData iTest_data(const AABB2D &ac, const Plane2D &bc)
	{
		if (iTest(ac, bc))
		{
			CollisionData r;
			r.collisionNormal = bc.normal;
			r.penDepth = dot(bc.normal, (ac.pos() - bc.position));
			if (r.penDepth < 0) r.penDepth = 0;
			return r;
		}
		else return CollisionData{ 0,0 };
	}

	CollisionData iTest_data(const AABB2D &ac, const Ray2D &bc)
	{
		if (iTest(ac, bc))
		{
			ConvexHull2D a;

			a.size = 4;

			a.verts[0] = ac.min;
			a.verts[1] = Vector2{ ac.min.x, ac.max.y };
			a.verts[2] = ac.max;
			a.verts[3] = Vector2{ ac.max.y, ac.min.y };

			return iTest_data(a, bc);
		}
		else return CollisionData{ 0,0 };
	}

	CollisionData iTest_data(const AABB2D &ac, const ConvexHull2D &bc)
	{
		return iTest_data(bc, ac);
	}

#pragma endregion

	void DebugAABB2D()
	{
#pragma region TestShapes

		AABB2D ab(Vector2{ 10 , 10 }, Vector2{ 20 , 20 });
		AABB2D bb(Vector2{ 15 , 15 }, Vector2{ 25 , 25 });
		AABB2D cb(Vector2{ 25 , 25 }, Vector2{ 35 , 35 });

		Circle ac{ Vector2{10 , 15 }, 5 };
		Circle bc{ Vector2{0  , 0  }, 1 };
		Circle cc{ Vector2{25 , 25 }, 5 };

		Plane2D ap{ Vector2{15 ,15 } , Vector2{0 ,1 } };
		Plane2D bp{ Vector2{15 ,15 } , Vector2{1 ,0 } };
		Plane2D cp{ Vector2{0  ,0  } , Vector2{0 ,1 } };

		Ray2D ar{ Vector2{0,0 }, normal(Vector2{0.5,0.5}), 50 };
		Ray2D br{ Vector2{14.9f,1}, Vector2{0,1}, 50 };
		Ray2D cr{ Vector2{1,13}, Vector2{1,0}, 50 };

		ConvexHull2D chull;

		chull.size = 4;
		chull.verts[0] = Vector2{ 20,22 };
		chull.verts[1] = Vector2{ 23,18 };
		chull.verts[2] = Vector2{ 26,22 };
		chull.verts[3] = Vector2{ 23,28 };

#pragma endregion

		//AABB2D VS AABB2D
		assert( iTest(ab, bb));
		assert(!iTest(ab, cb));
		assert( iTest(bb, cb));

		//AABB2D VS CIRCLE
		assert( iTest(ab, ac));
		assert(!iTest(ab, bc));
		assert(!iTest(ab, cc));

		assert( iTest(bb, ac));
		assert(!iTest(bb, bc));
		assert( iTest(bb, cc));

		assert(!iTest(cb, ac));
		assert(!iTest(cb, bc));
		assert( iTest(cb, cc));

		//AABB2D VS PLANE
		assert( iTest(ab, ap));
		assert( iTest(ab, bp));
		assert(!iTest(ab, cp));

		assert( iTest(bb, ap));
		assert( iTest(bb, bp));
		assert(!iTest(bb, cp));

		assert(!iTest(cb, ap));
		assert(!iTest(cb, bp));
		assert(!iTest(cb, cp));

		//AABB2D VS RAY2D
		assert( iTest(ab, ar));
		assert( iTest(ab, br));
		assert( iTest(ab, cr));

		assert( iTest(bb, ar));
		assert(!iTest(bb, br));
		assert(!iTest(bb, cr));

		assert( iTest(cb, ar));
		assert(!iTest(cb, br));
		assert(!iTest(cb, cr));

		//AABB VS CONVEX2D
		assert(iTest_data(chull, ab).penDepth <= 0);
		assert(iTest_data(chull, bb).penDepth  > 0);
		assert(iTest_data(chull, cb).penDepth <= 0);
	}

}