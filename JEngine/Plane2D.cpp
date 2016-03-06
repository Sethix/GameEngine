#include <cassert>
#include <algorithm>
#include "Plane2D.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix3.h"
#include "AABB2D.h"
#include "Circle.h"
#include "Ray2D.h"
#include "ConvexHull2D.h"

namespace JTL
{

	Plane2D	operator*	(const Matrix3 &m, const Plane2D &a)
	{
		Vector3 np = { a.position.x, a.position.y, 0 };
		Vector3 nr = { a.normal.x  , a.normal.y  , 0 };
		np = (m * np);
		nr = (m * nr);
		return Plane2D{ np.xy, normal(nr.xy) };
	}

#pragma region ShapeFunctions

	bool iTest(const Plane2D &ac, const AABB2D &bc)
	{
		return iTest(bc, ac);
	}

	bool iTest(const Plane2D &ac, const Circle &bc)
	{
		return iTest(bc, ac);
	}

	bool iTest(const Plane2D &ac, const Ray2D &bc)
	{
		return iTest(bc, ac);
	}

	CollisionData iTest_data(const Plane2D &ac, const AABB2D &bc)
	{
		return iTest_data(bc, ac);
	}

	CollisionData iTest_data(const Plane2D &ac, const Circle &bc)
	{
		return iTest_data(bc, ac);
	}

	CollisionData iTest_data(const Plane2D &ac, const Ray2D &bc)
	{
		return iTest_data(bc, ac);
	}

	CollisionData iTest_data(const Plane2D &ac, const ConvexHull2D &bc)
	{
		return iTest_data(bc, ac);
	}

#pragma endregion

	void DebugPlane()
	{
#pragma region TestShapes

		AABB2D ab(Vector2{ 10 , 10 }, Vector2{ 20 , 20 });
		AABB2D bb(Vector2{ 15 , 15 }, Vector2{ 25 , 25 });
		AABB2D cb(Vector2{ 25 , 25 }, Vector2{ 35 , 35 });

		Circle ac{ Vector2{ 20, 20 }, 5 };
		Circle bc{ Vector2{ 10  , 10 }, 8 };
		Circle cc{ Vector2{ 25 , 25 }, 5 };

		Plane2D ap{ Vector2{ 15 ,15 } , Vector2{ 0 ,1 } };
		Plane2D bp{ Vector2{ 15 ,15 } , Vector2{ 1 ,0 } };
		Plane2D cp{ Vector2{ 1  ,1 } , Vector2{ 0 ,-1 } };

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

		//PLANE VS AABB2D
		assert(iTest(ab, ap));
		assert(iTest(ab, bp));
		assert(iTest(ab, cp));

		assert(iTest(bb, ap));
		assert(iTest(bb, bp));
		assert(iTest(bb, cp));

		assert(!iTest(cb, ap));
		assert(!iTest(cb, bp));
		assert(iTest(cb, cp));

		//PLANE VS CIRCLE
		assert(iTest(ac, ap));
		assert(iTest(ac, bp));
		assert(iTest(ac, cp));

		assert(iTest(bc, ap));
		assert(iTest(bc, bp));
		assert(iTest(bc, cp));

		assert(!iTest(cc, ap));
		assert(!iTest(cc, bp));
		assert(iTest(cc, cp));

		//PLANE VS RAY2D
		assert(!iTest(ap, ar));
		assert(!iTest(ap, br));
		assert(!iTest(ap, cr));

		assert(!iTest(bp, ar));
		assert(!iTest(bp, br));
		assert(!iTest(bp, cr));

		assert( iTest(cp, ar));
		assert( iTest(cp, br));
		assert(!iTest(cp, cr));

		//PLANE VS CONVEX2D
		assert(iTest_data(chull, ap).penDepth <= 0);
		assert(iTest_data(chull, bp).penDepth <= 0);
		assert(iTest_data(chull, cp).penDepth  > 0);
	}
}