/******************************************************

----------------------Collider.h-----------------------

	Purpose -
		To provide a container to be used in
		testing intersection between two objects.



	Functionality -
		Capable of the following,


		* Intersection test between two objects.

			(CollisionData isColliding(Transform&, Collider&, 
									   Transform&, Collider&))



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
#include "AABB2D.h"
#include "Circle.h"
#include "Ray2D.h"
#include "Plane2D.h"
#include "ConvexHull2D.h"

namespace JTL
{
	class Transform;

	class Collider
	{
	public:
		enum SHAPE { e_CIRCLE = 1, e_AABB = 2, e_RAY = 4, e_PLANE = 8, e_CONVEX = 16 } shape;
		
		union
		{
			Circle			circle;
			AABB2D			aabb;
			Ray2D			ray;
			Plane2D			plane;
			ConvexHull2D	chull;
		};

		bool isTrigger;
		Collider();
	};

	CollisionData isColliding(const Transform &, const Collider &,
							  const Transform &, const Collider &);

}