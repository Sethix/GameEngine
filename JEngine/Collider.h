#pragma once
#include "AABB2D.h"
#include "Circle.h"
#include "Ray2D.h"
#include "Plane.h"
#include "ConvexHull2D.h"

namespace JTL
{
	class Transform;

	class Collider
	{
	public:
		enum SHAPE { e_CIRCLE = 1, e_AABB = 2, e_RAY = 4, e_PLANE = 8 } shape;

		bool isTrigger;


		union
		{
			Circle  circle;
			AABB2D    aabb;
			Ray2D      ray;
			Plane    plane;
		};

		Collider();
		ConvexHull2D chull;
	};

	CollisionData isColliding(const Transform &at, const Collider &ac,
							  const Transform &bt, const Collider &bc);

}