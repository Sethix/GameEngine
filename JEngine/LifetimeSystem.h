#pragma once
#include "System.h"
#include "Time.h"

namespace JTL
{
	class LifetimeSystem : public System
	{
		bool condition(Handle<Entity> i)
		{
			return i->lifespan > -1;
		}

		bool update(Handle<Entity> i)
		{
			if (i->lifespan->curTime >= i->lifespan->timeLimit) 
				Entity::free(i);
			else
				i->lifespan->curTime += Time::instance().getDeltaTime();
			return true;
		}
	};
}