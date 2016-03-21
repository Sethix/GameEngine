#pragma once
#include "System.h"
#include "Asset.h"

namespace JTL
{

	class RenderSystem : public System
	{
		bool condition(Handle<Entity> i)
		{
			return i->camera > -1;
		}

		bool update(Handle<Entity> i)
		{
			i->camera->update();
			return true;
		}
	};

}