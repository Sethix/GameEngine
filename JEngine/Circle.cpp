#include <cassert>
#include <algorithm>
#include "Circle.h"
#include "JMath.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix3.h"
#include "Circle.h"
#include "AABB2D.h"
#include "Plane.h"
#include "Ray2D.h"
#include "ConvexHull2D.h"

namespace JTL
{

	Circle	operator*	(const Matrix3 &m, const Circle &a)
	{
		Circle r;
		r.radius = fmaxf(mag(m*Vector3{ a.radius,0,0 }),
					     mag(m*Vector3{ 0,a.radius,0 }));

		r.position = (m * Vector3{a.position.x, a.position.y, 1}).xy;
		return r;
	}

#pragma region CollisionFunctions

	bool	iTest(const Circle &ac, const Circle &bc)
	{
		return sqrtf((bc.position.x - ac.position.x) * (bc.position.x - ac.position.x) 
			       + (bc.position.y - ac.position.y) * (bc.position.y - ac.position.y)) 
			      <= (ac.radius + bc.radius);
	}

	bool	iTest(const Circle &ac, const AABB2D &bc)
	{
		return iTest(Circle{ clamp(ac.position, bc.min, bc.max) , 0 }, ac);
	}

	bool	iTest(const Circle &ac, const Plane &bc)
	{
		return bc.normal.x * (ac.position.x - bc.position.x) <= ac.radius &&
			   bc.normal.y * (ac.position.y - bc.position.y) <= ac.radius;
	}

	bool	iTest(const Circle &ac, const Ray2D &bc)
	{
		Vector2 pc = bc.position + bc.direction * fclamp(dot((ac.position - bc.position), bc.direction), 0, bc.length);
		return dot(ac.position - pc, ac.position - pc)
			<=  (ac.radius * ac.radius);
	}

	CollisionData iTest_data(const Circle &ac, const Circle &bc)
	{
		if (iTest(ac, bc))
		{
			return CollisionData{ (bc.position.x - ac.position.x) * (bc.position.x - ac.position.x   )
								+ (bc.position.y - ac.position.y) * (bc.position.y - ac.position.y   )
								- (ac.radius + bc.radius        ) ,  normal(bc.position - ac.position) };
		}
		else return CollisionData{ 0,0 };
	}

	CollisionData iTest_data(const Circle &ac, const AABB2D &bc)
	{
		if (iTest(bc, ac))
		{
			ConvexHull2D a;

			a.size = 4;

			a.verts[0] = bc.min;
			a.verts[1] = Vector2{ bc.min.x, bc.max.y };
			a.verts[2] = bc.max;
			a.verts[3] = Vector2{ bc.max.y, bc.min.y };

			return iTest_data(a, ac);
		}
		else return CollisionData{ 0,0 };
	}

	CollisionData iTest_data(const Circle &ac, const Plane &bc)
	{
		if (iTest(ac, bc))
		{
			return CollisionData{ fmaxf(bc.normal.x * (ac.position.x - bc.position.x) + ac.radius,
									    bc.normal.y * (ac.position.y - bc.position.y) + ac.radius), bc.normal };
		}
		else return CollisionData{ 0,0 };
	}

	CollisionData iTest_data(const Circle &ac, const Ray2D &bc)
	{
		if (iTest(ac, bc))
		{
			Vector2 pc = bc.position + bc.direction * fclamp(dot((ac.position - bc.position), bc.direction), 0, bc.length);
			return CollisionData{ dot(pc - bc.position, pc - bc.position) + (ac.radius * ac.radius), perp(bc.direction) };
		}
		else return CollisionData{ 0,0 };
	}

#pragma endregion

	void DebugCircle()
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
		Plane cp{ Vector2{ 0  ,0 } , Vector2{ 0 ,1 } };

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

		//CIRCLE VS CIRCLE
		assert(!iTest(ac, bc));
		assert( iTest(ac, cc));
		assert(!iTest(bc, cc));

		//CIRCLE VS AABB
		assert( iTest(ab, ac));
		assert( iTest(ab, bc));
		assert(!iTest(ab, cc));

		assert( iTest(bb, ac));
		assert( iTest(bb, bc));
		assert( iTest(bb, cc));

		assert(!iTest(cb, ac));
		assert(!iTest(cb, bc));
		assert( iTest(cb, cc));

		//CIRCLE VS PLANE
		assert( iTest(ac, ap));
		assert( iTest(ac, bp));
		assert(!iTest(ac, cp));

		assert( iTest(bc, ap));
		assert( iTest(bc, bp));
		assert(!iTest(bc, cp));

		assert(!iTest(cc, ap));
		assert(!iTest(cc, bp));
		assert(!iTest(cc, cp));

		//CIRCLE VS RAY2D
		assert( iTest(ac, ar));
		assert(!iTest(ac, br));
		assert(!iTest(ac, cr));

		assert( iTest(bc, ar));
		assert( iTest(bc, br));
		assert( iTest(bc, cr));

		assert( iTest(cc, ar));
		assert(!iTest(cc, br));
		assert(!iTest(cc, cr));

		//CIRCLE VS CONVEX2D
		assert(iTest_data(chull, ac).penDepth  > 0);
		assert(iTest_data(chull, bc).penDepth <= 0);
		assert(iTest_data(chull, cc).penDepth  > 0);
	}
}