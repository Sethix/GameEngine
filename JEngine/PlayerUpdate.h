#pragma once
#include "System.h"
#include "Input.h"
#include "Time.h"

namespace JTL
{
	class PlayerUpdate : public System
	{
		bool condition(Handle<Entity> i)
		{
			return  i->rigidbody  > -1 &&
					i->transform  > -1 &&
					i->controller > -1;
		}

		bool update(Handle<Entity> i)
		{
			auto &input = Input::instance();
			auto controller = *i->controller;
			
			float dt = Time::instance().getDeltaTime();

			if (controller.gamepad == false)
			{

				if (input.getKey(controller.LEFT) && i->rigidbody->velocity.x > -controller.maxSpeed)
					i->rigidbody->addForce({ -controller.moveSpeed, 0 });

				if (input.getKey(controller.RIGHT) && i->rigidbody->velocity.x < controller.maxSpeed)
					i->rigidbody->addForce({ controller.moveSpeed, 0 });

				if (input.getKeyPress(controller.JUMP) && controller.grounded)
					i->rigidbody->addForce({ 0, controller.jumpForce });

			}
			else
			{
				if (input.getJoy(controller.PlayerNumber, controller.LEFT) && i->rigidbody->velocity.x > -controller.maxSpeed)
					i->rigidbody->addForce({ -controller.moveSpeed, 0 });

				if (input.getJoy(controller.PlayerNumber, controller.RIGHT) && i->rigidbody->velocity.x < controller.maxSpeed)
					i->rigidbody->addForce({ controller.moveSpeed, 0 });

				if (input.getJoyPress(controller.PlayerNumber, controller.JUMP) && controller.grounded)
					i->rigidbody->addForce({ 0, controller.jumpForce });
			}

			if(i->rigidbody->velocity.y > -i->controller->terminalVelocity)
				i->rigidbody->addForce({ 0, -controller.gravity });

			if (i->rigidbody->velocity.y < -i->controller->terminalVelocity)
			{
				i->rigidbody->velocity.y = -i->controller->terminalVelocity;
			}

			return true;
		}
	};
}