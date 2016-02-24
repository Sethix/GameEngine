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
		return dot(pc - bc.position, pc - bc.position)
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


		/*assert(!iTest(ac, cc));
		assert(!iTest(ac, bc));
		assert(!iTest(bc, cc));*/
	}
}