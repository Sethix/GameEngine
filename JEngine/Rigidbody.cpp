#include "Rigidbody.h"

namespace JTL
{

	Rigidbody::Rigidbody() :
		acceleration({ 0,0 }), velocity({ 0,0 }), mass(1),
		force({ 0,0 }), drag(0), angularVelocity(0), angularAcceleration(0), 
		torque(0), angularDrag(0){}

	void Rigidbody::addForce(const Vector2 &a)
	{
		force = force + a;
	}

	void Rigidbody::addTorque(const float &a)
	{
		torque = torque + a;
	}

	void Rigidbody::integrate(Transform *t, float dt)
	{
		jerk = force / mass - acceleration;
		angularJerk = torque / mass - angularAcceleration;

		acceleration = acceleration + jerk * dt;
		angularAcceleration = angularAcceleration + angularJerk * dt;

		velocity = velocity + acceleration * dt;
		angularVelocity = angularVelocity + angularAcceleration * dt;

		t->setPosition(t->getPosition() + velocity * dt);
		t->setAngle(t->getAngle() + angularVelocity * dt);

		velocity = velocity - velocity * drag * dt;
		angularVelocity = angularVelocity - angularVelocity * angularDrag * dt;

		force = { 0, 0 };
		torque = 0;
	}

}