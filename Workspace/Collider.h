#pragma once
#include "AABB.h"
#include "Circle.h"
#include "Ray.h"
#include "Plane.h"
#include "ConvexHull.h"

namespace JTL
{

	class Transform;

	class Collider
	{
	public:
		enum SHAPE { e_CIRCLE = 1, e_AABB = 2, e_RAY = 4, e_PLANE = 8 } shape;
		union
		{
			Circle  circle;
			AABB    aabb;
			Ray     ray;
			Plane   plane;
		};

		Collider();
		ConvexHull chull;
	};

	CollisionData isColliding(const Transform &at, const Collider &ac,
							  const Transform &bt, const Collider &bc);


}