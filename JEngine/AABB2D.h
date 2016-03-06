/******************************************************

-----------------------AABB2D.h------------------------

	Purpose -
		Represents an axis aligned bounding box in
		2-Dimensional space for collision testing.



	Functionality -
		Capable of the following,


		* Multiplication between AABB and Matrix3 to apply transformation

			(*, *=)

		* Generate an AABB from an array of vectors

			(AABB2D genAABB2D(Vector2*, size_t))

		* Rotate an AABB using an angle

			(AABB2D rotate(AABB2D, float))

		* Check if two shapes are intersecting

			(bool iTest(Shape, Shape))

		* Run test cases to make sure all functions work

			(void DebugAABB2D())



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

	struct Circle;
	struct Plane2D;
	struct Ray2D;
	struct ConvexHull2D;
	
	struct CollisionData;

#pragma endregion

	struct AABB2D
	{

		AABB2D(const Vector2 &bl, const Vector2 &tr) : min(bl), max(tr) {};

		Vector2 min, max;

		Vector2 dim() const;

		Vector2 pos() const;

	};

#pragma region ShapeFunctions

	AABB2D operator*(const Matrix3 &m, const AABB2D &a);

	AABB2D genAABB2D(const Vector2 *pts, const size_t &n);

	AABB2D rotate(const AABB2D &x, const float &a);

#pragma endregion

#pragma region CollisionFunctions

	bool iTest(const AABB2D &ac, const AABB2D &bc);

	bool iTest(const AABB2D &ac, const Circle &bc);

	bool iTest(const AABB2D &ac, const Plane2D &bc);

	bool iTest(const AABB2D &ac, const Ray2D &bc);

	CollisionData iTest_data(const AABB2D &ac, const AABB2D &bc);

	CollisionData iTest_data(const AABB2D &ac, const Circle &bc);

	CollisionData iTest_data(const AABB2D &ac, const Plane2D &bc);

	CollisionData iTest_data(const AABB2D &ac, const Ray2D &bc);

	CollisionData iTest_data(const AABB2D &ac, const ConvexHull2D &bc);

#pragma endregion

	void DebugAABB2D();

}