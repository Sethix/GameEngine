#pragma once
#include "System.h"
#include "Time.h"

namespace JTL
{
	class HealthSystem : public System
	{
		bool condition(Handle<Entity> i)
		{
			return i->health > -1;
		}

		bool update(Handle<Entity> i)
		{
			i->health->setCurrentHeath(i->health->getCurrentHealth() + (i->health->getRegenRate()) * Time::instance().getDeltaTime());
			if (i->health->getCurrentHealth() > i->health->getMaxHealth()) i->health->setCurrentHeath(i->health->getMaxHealth());

			if (i->health->getCurrentHealth() <= 0) Entity::free(i);

			return true;
		}
	};
}