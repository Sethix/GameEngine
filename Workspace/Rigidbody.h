#pragma once
#include "Vector2.h"
#include "Transform.h"

namespace JTL
{

	class Rigidbody
	{
	public:
		Vector2 velocity, acceleration, force, jerk;
		float mass, drag;

		float angularVelocity, angularAcceleration, torque;
		float angularDrag;

		Rigidbody();
		void addForce(const Vector2 &);
		void addTorque(const float &);
		void integrate(Transform *, float dt);
	};

}