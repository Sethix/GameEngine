/******************************************************

--------------------ConvexHull2D.h---------------------

	Purpose -
		Represents a convex polygonal shape in 
		2-Dimensional space for collision testing.



	Functionality -
		Capable of the following,


		* Multiplication between convex hull and Matrix3 to apply transformation

			(*, *=)

		* Check if two shapes are intersecting

			(bool iTest(Shape, Shape))

		* Run test cases to make sure all functions work

			(void DebugConvex2D())



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
#include "Vector2.h"

namespace JTL
{
	
#pragma region ForwardDeclarations

	struct Matrix3;

	struct AABB2D;
	struct Circle;
	struct Plane2D;
	struct Ray2D;

#pragma endregion

	struct CollisionData
	{
		float penDepth;
		Vector2 collisionNormal;
	};

	struct ConvexHull2D
	{
		Vector2 verts[32];
		size_t size;
	};

	ConvexHull2D operator*(const Matrix3 &m, const ConvexHull2D &a);

#pragma region CollisionFunctions

	CollisionData iTest_data(const ConvexHull2D &a, const ConvexHull2D &b);

	CollisionData iTest_data(const ConvexHull2D &a, const AABB2D &b);

	CollisionData iTest_data(const ConvexHull2D &a, const Circle &b);

	CollisionData iTest_data(const ConvexHull2D &a, const Plane2D &b);

	CollisionData iTest_data(const ConvexHull2D &a, const Ray2D &b);

#pragma endregion

	void DebugConvex2D();

}