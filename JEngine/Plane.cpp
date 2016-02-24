#include <algorithm>
#include "Plane.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Matrix3.h"
#include "AABB2D.h"
#include "Circle.h"
#include "Ray2D.h"
#include "ConvexHull2D.h"

namespace JTL
{

	Plane	operator*	(const Matrix3 &m, const Plane &a)
	{
		Vector3 np = { a.position.x, a.position.y, 0 };
		Vector3 nr = { a.normal.x  , a.normal.y  , 0 };
		np = (m * np);
		nr = (m * nr);
		return Plane{ np.xy, normal(nr.xy) };
	}

#pragma region ShapeFunctions

	bool iTest(const Plane &ac, const AABB2D &bc)
	{
		return iTest(bc, ac);
	}

	bool iTest(const Plane &ac, const Circle &bc)
	{
		return iTest(bc, ac);
	}

	bool iTest(const Plane &ac, const Ray2D &bc)
	{
		return iTest(bc, ac);
	}

	CollisionData iTest_data(const Plane &ac, const AABB2D &bc)
	{
		return iTest_data(bc, ac);
	}

	CollisionData iTest_data(const Plane &ac, const Circle &bc)
	{
		return iTest_data(bc, ac);
	}

	CollisionData iTest_data(const Plane &ac, const Ray2D &bc)
	{
		return iTest_data(bc, ac);
	}

#pragma endregion

	void DebugPlane()
	{

	}
}