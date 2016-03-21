#pragma once
#include "System.h"
#include "Time.h"

namespace JTL
{
	class RigidbodyDynamics : public System
	{
		bool condition(Handle<Entity> i)
		{
			return i->transform > -1 && i->rigidbody > -1;
		}

		bool update(Handle<Entity> i)
		{
			i->rigidbody->integrate(&i->transform, Time::instance().getDeltaTime());
			return true;
		}
	};
}