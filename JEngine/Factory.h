#pragma once
#include "Entity.h"

namespace JTL
{

	struct Factory
	{
		static Handle<Entity> CreateBox(Vector2 pos, Vector2 vel, Vector2 dim, float mass)
		{
			auto e = Entity::make();

			e->collider = Collider::make();
			e->rigidbody = Rigidbody::make();
			e->transform = Transform::make();

			e->collider->aabb.min = pos - (dim / 2);
			e->collider->aabb.max = pos + (dim / 2);
			e->collider->shape = Collider::e_AABB;
			e->rigidbody->mass = mass;
			e->rigidbody->velocity = vel;
			e->transform->setPosition(pos);

			return e;
		}

		static Handle<Entity> CreateBall(Vector2 pos, Vector2 vel, float radius, float mass)
		{
			auto e = Entity::make();

			e->collider	 = Collider::make();
			e->rigidbody = Rigidbody::make();
			e->transform = Transform::make();

			e->collider->circle.radius = radius;
			e->collider->shape = Collider::e_CIRCLE;
			e->rigidbody->mass = mass;
			e->rigidbody->velocity = vel;
			e->transform->setPosition(pos);

			return e;
		}

		static Handle<Entity> CreatePlane(Vector2 pos, Vector2 normal)
		{
			auto e = Entity::make();

			e->collider = Collider::make();
			e->transform = Transform::make();

			e->collider->plane.normal = normal;
			e->collider->shape = Collider::e_PLANE;
			e->transform->setPosition(pos);

			return e;
		}

		static Handle<Entity> CreateRay(Vector2 pos, Vector2 direction, float length)
		{
			auto e = Entity::make();

			e->collider = Collider::make();
			e->transform = Transform::make();

			e->collider->ray.direction = direction;
			e->collider->ray.length = length;
			e->collider->shape = Collider::e_RAY;
			e->transform->setPosition(pos);

			return e;
		}

		static Handle<Entity> CreateConvex(Vector2 pos, Vector2 vel, Vector2* points, float size, float mass)
		{
			auto e = Entity::make();

			e->collider = Collider::make();
			e->rigidbody = Rigidbody::make();
			e->transform = Transform::make();

			for (unsigned i = 0; i < size; ++i)
				e->collider->chull.verts[i] = points[i];

			e->collider->shape = Collider::e_CONVEX;
			e->rigidbody->mass = mass;
			e->rigidbody->velocity = vel;
			e->transform->setPosition(pos);

			return e;
		}
	};

}