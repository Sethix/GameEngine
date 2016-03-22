#pragma once
#include "System.h"
#include "Time.h"

namespace JTL
{
	class ManaSystem : public System
	{
		bool condition(Handle<Entity> i)
		{
			return i->mana > -1;
		}

		bool update(Handle<Entity> i)
		{
			i->mana->setCurrentMana(i->mana->getCurrentMana() + i->mana->getRegenRate());
			if (i->mana->getCurrentMana() > i->mana->getMaxMana()) i->mana->setCurrentMana(i->mana->getMaxMana());
			return true;
		}
	};
}