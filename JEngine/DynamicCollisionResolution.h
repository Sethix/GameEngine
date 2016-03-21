/******************************************************

--------------DynamicCollisionResolution.h-------------

	Purpose -
		A system used to sort through stored
		collision data and handle collision between
		dynamic entities.



	Credits -
		Justin T Hamm -
			- Creator of JTL -

		Esmeralda Salamone -
			- Programming Instructor -

		Terry Nguyen -
			- Assistant Instructor -



	License -
		The MIT License (MIT)

			Copyright (c) [2016] [Justin T Hamm]

			Permission is hereby granted, free of charge, to any person obtaining a copy
			of this software and associated documentation files (the "Software"), to deal
			in the Software without restriction, including without limitation the rights
			to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
			copies of the Software, and to permit persons to whom the Software is
			furnished to do so, subject to the following conditions:

			The above copyright notice and this permission notice shall be included in all
			copies or substantial portions of the Software.

			THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
			IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
			FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
			AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
			LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
			OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
			SOFTWARE.


*******************************************************/

#pragma once
#include "CollisionDetection.h"

namespace JTL
{
	class DynamicResolution : public CollisionSystem
	{
		bool condition(Collision &c)
		{
			return c.first->rigidbody > -1 && c.second->rigidbody > -1 
				&& c.first->collider->isTrigger == false
				&& c.second->collider->isTrigger == false;
		}

		void update(Collision &c)
		{
			Vector2 MTV = c.collision.collisionNormal * c.collision.penDepth;

			Vector2 p1 = c.first->transform->getPosition() - MTV / 2;
			Vector2 p2 = c.second->transform->getPosition() + MTV / 2;

			c.first->transform->setPosition(p1);
			c.second->transform->setPosition(p2);

			std::swap(c.first->rigidbody->velocity, c.second->rigidbody->velocity);
		}
	};
}