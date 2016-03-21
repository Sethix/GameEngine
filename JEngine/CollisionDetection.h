/******************************************************

------------------CollisionDetection.h-----------------

	Purpose -
		A system used to sort through entities and
		store collisions.



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
#include "System.h"
#include "Entity.h"

namespace JTL
{
	struct Collision
	{
		Handle<Entity> first, second;
		CollisionData collision;

		static std::vector<Collision> &getData()
		{
			static std::vector<Collision> data;
			return data;
		}
	};

	class CollisionSystem
	{
		virtual bool condition(Collision &a) = 0;
		virtual void update(Collision &a) = 0;
		virtual void onStep() {}
	public:
		void step()
		{
			onStep();
			for each(Collision c in Collision::getData())
				if(condition(c) == true)
					update(c);
		}
	};

	class CollisionDetection : public BinarySystem
	{
		void onStep() { Collision::getData().clear(); }

		bool condition(Handle<Entity> i) { return i->transform > -1 && i->collider > -1; }

		void update(Handle<Entity> i, Handle<Entity> j)
		{
			auto cd = isColliding(*i->transform, *i->collider, *j->transform, *j->collider);
			if (cd.penDepth > 0) Collision::getData().push_back(Collision{ i,j,cd });
		}
	};
}