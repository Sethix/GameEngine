#pragma once
#include "ComponentData.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "Transform.h"

namespace JTL
{

	struct Entity : ComponentData<Entity>
	{
		Handle<Transform> transform;
		Handle<Rigidbody> rigidbody;
		Handle<Collider > collider;

		void onFree()
		{
			Transform::free(transform.index);
			Rigidbody::free(rigidbody.index);
			Collider ::free(collider.index);
		}
	};

}