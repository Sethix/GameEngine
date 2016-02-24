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
		float r = mag(bc.normal * (ac.position - bc.position) / -(bc.normal * ac.direction));
		return 0 <= r && r <= ac.length;
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

	}
}