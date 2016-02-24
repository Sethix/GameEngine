#include <cassert>
#include <algorithm>
#include "Ray2D.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix3.h"
#include "AABB2D.h"
#include "Circle.h"
#include "Plane.h"
#include "ConvexHull2D.h"

namespace JTL
{

	Ray2D	operator*	(const Matrix3 &m, const Ray2D &a)
	{
		Vector3 np = { a.position.x, a.position.y, 0 };
		Vector3 nr = { a.direction.x  , a.direction.y  , 0 };
		np = (m * np);
		nr = (m * nr);
		return Ray2D{ np.xy, normal(nr.xy), a.length };
	}

#pragma region ShapeFunctions

	bool iTest(const Ray2D &ac, const AABB2D &bc)
	{
		return iTest(bc, ac);
	}

	bool iTest(const Ray2D &ac, const Circle &bc)
	{
		return iTest(bc, ac);
	}

	bool iTest(const Ray2D &ac, const Plane &bc)
	{
		float r = dot(bc.normal, (ac.position - bc.position)) / -(dot(bc.normal, ac.direction));
		return 0 <= r && r <= ac.length && -(dot(bc.normal, ac.direction)) > 0;
	}

	CollisionData iTest_data(const Ray2D &ac, const AABB2D &bc)
	{
		return iTest_data(bc, ac);
	}

	CollisionData iTest_data(const Ray2D &ac, const Circle &bc)
	{
		return iTest_data(ac, bc);
	}

	CollisionData iTest_data(const Ray2D &ac, const Plane &bc)
	{
		CollisionData cd = { 0 };
		float r = mag(bc.normal * (ac.position - bc.position) / -(bc.normal * ac.direction));
		if (r <= 0 && r <= ac.length) cd = { r, perp(bc.normal) };
		return cd;
	}

#pragma endregion

	void DebugRay2D()
	{
#pragma region TestShapes

		AABB2D ab(Vector2{ 10 , 10 }, Vector2{ 20 , 20 });
		AABB2D bb(Vector2{ 15 , 15 }, Vector2{ 25 , 25 });
		AABB2D cb(Vector2{ 25 , 25 }, Vector2{ 35 , 35 });

		Circle ac{ Vector2{ 20, 20 }, 5 };
		Circle bc{ Vector2{ 10  , 10 }, 8 };
		Circle cc{ Vector2{ 25 , 25 }, 5 };

		Plane ap{ Vector2{ 15 ,15 } , Vector2{ 0 ,1 } };
		Plane bp{ Vector2{ 15 ,15 } , Vector2{ 1 ,0 } };
		Plane cp{ Vector2{ 1  ,1 } , Vector2{ 0 ,-1 } };

		Ray2D ar{ Vector2{ 0,0 }, normal(Vector2{ 0.5,0.5 }), 50 };
		Ray2D br{ Vector2{ 14.9f,1 }, Vector2{ 0,1 }, 50 };
		Ray2D cr{ Vector2{ 1,13 }, Vector2{ 1,0 }, 50 };

		ConvexHull2D chull;

		chull.size = 4;
		chull.verts[0] = Vector2{ 20,22 };
		chull.verts[1] = Vector2{ 23,18 };
		chull.verts[2] = Vector2{ 26,22 };
		chull.verts[3] = Vector2{ 23,28 };

#pragma endregion

		//RAY2D VS AABB2D
		assert(iTest(ab, ar));
		assert(iTest(ab, br));
		assert(iTest(ab, cr));

		assert(iTest(bb, ar));
		assert(!iTest(bb, br));
		assert(!iTest(bb, cr));

		assert(iTest(cb, ar));
		assert(!iTest(cb, br));
		assert(!iTest(cb, cr));

		//RAY2D VS CIRCLE
		assert(iTest(ac, ar));
		assert(!iTest(ac, br));
		assert(!iTest(ac, cr));

		assert(iTest(bc, ar));
		assert(iTest(bc, br));
		assert(iTest(bc, cr));

		assert(iTest(cc, ar));
		assert(!iTest(cc, br));
		assert(!iTest(cc, cr));

		//RAY2D VS PLANE
		assert(!iTest(ap, ar));
		assert(!iTest(ap, br));
		assert(!iTest(ap, cr));

		assert(!iTest(bp, ar));
		assert(!iTest(bp, br));
		assert(!iTest(bp, cr));

		assert(iTest(cp, ar));
		assert(iTest(cp, br));
		assert(!iTest(cp, cr));

		//RAY2D VS CONVEX2D
		assert(iTest_data(chull, ar).penDepth  > 0);
		assert(iTest_data(chull, br).penDepth  > 0);
		assert(iTest_data(chull, cr).penDepth <= 0);
	}
}