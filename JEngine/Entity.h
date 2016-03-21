// TODO : Documentation

#pragma once
#include "ComponentData.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "Transform.h"
#include "Camera.h"
#include "Sprite.h"
#include "Lifetime.h"
#include "Health.h"
#include "Mana.h"
#include "PlayerController.h"

namespace JTL
{

	struct Entity : ComponentData<Entity>
	{
		Handle<Transform		> transform;
		Handle<Rigidbody		> rigidbody;
		Handle<Collider			> collider;
		Handle<Camera			> camera;
		Handle<Sprite			> sprite;
		Handle<PlayerController	> controller;
		Handle<Lifespan			> lifespan;
		Handle<Health			> health;
		Handle<Mana				> mana;

		void onFree()
		{
			Transform		 ::free(transform.index);
			Rigidbody		 ::free(rigidbody.index);
			Collider		 ::free(collider.index);
			Camera			 ::free(camera.index);
			Sprite			 ::free(sprite.index);
			PlayerController ::free(controller.index);
			Lifespan		 ::free(lifespan.index);
			Health			 ::free(health.index);
			Mana			 ::free(mana.index);
		}
	};

}