#include "Collider.h"
#include "Transform.h"

namespace JTL
{
	Collider::Collider() : shape(Collider::e_CIRCLE), circle({ {0,0},1 }) { }

	CollisionData isColliding(const Transform &at, const Collider &ac,
							  const Transform &bt, const Collider &bc)
	{
		Transform t_lhs = at;
		Transform t_rhs = bt;
		Collider lhs = ac;
		Collider rhs = bc;

		if (lhs.shape > rhs.shape)
		{
			std::swap(lhs, rhs);
			std::swap(t_lhs, t_rhs);
		}

#pragma region Shape_switch_statement

		switch (lhs.shape | rhs.shape)
		{
		case Collider::e_CIRCLE:
			return iTest_data(t_lhs.getGlobalTransform() * lhs.circle,
							  t_rhs.getGlobalTransform() * rhs.circle);
		case Collider::e_CIRCLE | Collider::e_AABB:
			return iTest_data(t_lhs.getGlobalTransform() * lhs.circle,
							  t_rhs.getGlobalTransform() * rhs.aabb);
		case Collider::e_CIRCLE | Collider::e_RAY:
			return iTest_data(t_lhs.getGlobalTransform() * lhs.circle,
							  t_rhs.getGlobalTransform() * rhs.ray);
		case Collider::e_CIRCLE | Collider::e_PLANE:
			return iTest_data(t_lhs.getGlobalTransform() * lhs.circle,
							  t_rhs.getGlobalTransform() * rhs.plane);
		case Collider::e_CIRCLE | Collider::e_CONVEX:
			return iTest_data(t_lhs.getGlobalTransform() * lhs.circle,
							  t_rhs.getGlobalTransform() * rhs.chull);

		case Collider::e_AABB:
			return iTest_data(t_lhs.getGlobalTransform() * lhs.aabb,
							  t_rhs.getGlobalTransform() * rhs.aabb);
		case Collider::e_AABB | Collider::e_RAY:
			return iTest_data(t_lhs.getGlobalTransform() * lhs.aabb,
							  t_rhs.getGlobalTransform() * rhs.ray);
		case Collider::e_AABB | Collider::e_PLANE:
			return iTest_data(t_lhs.getGlobalTransform() * lhs.aabb,
							  t_rhs.getGlobalTransform() * rhs.plane);
		case Collider::e_AABB | Collider::e_CONVEX:
			return iTest_data(t_lhs.getGlobalTransform() * lhs.aabb,
							  t_rhs.getGlobalTransform() * rhs.chull);

		case Collider::e_RAY | Collider::e_PLANE:
			return iTest_data(t_lhs.getGlobalTransform() * lhs.ray,
							  t_rhs.getGlobalTransform() * rhs.plane);
		case Collider::e_RAY | Collider::e_CONVEX:
			return iTest_data(t_lhs.getGlobalTransform() * lhs.ray,
							  t_rhs.getGlobalTransform() * rhs.chull);

		case Collider::e_PLANE | Collider::e_CONVEX:
			return iTest_data(t_lhs.getGlobalTransform() * lhs.plane,
							  t_rhs.getGlobalTransform() * rhs.chull);

		case Collider::e_CONVEX:
			return iTest_data(t_lhs.getGlobalTransform() * lhs.chull,
							  t_rhs.getGlobalTransform() * rhs.chull);
		}

#pragma endregion

	}
}