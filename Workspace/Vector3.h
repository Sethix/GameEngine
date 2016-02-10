/******************************************************

-----------------------Vector3.h-----------------------

	Purpose -
		Contains three floating point values.



	Functionality -
		Capable of the following,


		* Addition between vectors

			(+, +=)

		* Subtraction between vectors

			(-, -=)

		* Multiplication between vectors

			(*, *=)

		* Division between vectors

			(/, /=)

		* Imperfect equality comparison between vectors

			(==, !=, >, >=, <, <=)

		* Calculate the dot product of two vectors

			(float dot(Vector3, Vector3))

		* Calculate the length of a vector

			(float mag(Vector3))

		* Calculate the cross product between vectors

			(Vector3 cross(Vector3, Vector3)

		* Calculate the normal of a vector

			(Vector3 normal(Vector3))

		* Set the a vector to it's normal

			(Vector3 normalize())

		* Interpolate between two vectors using a value from 0-1

			(Vector3 lerp(Vector3(0), Vector3(1), float))

		* Clamp a vector inside a minimum and maximum point

			(Vector3 clamp(Vector3(A), Vector3(MIN), Vector3(MAX));

		* Grab the minimum values from an array of vectors

			(Vector3 min(Vector3*, size_t))

		* Grab the maximum values from an array of vectors

			(Vector3 max(Vector3*, size_t))

		* Calculate physcal reflection off of a normalized surface

			(Vector3 reflect(Vector3 incident, Vector3 normal))

		* Run test cases to make sure all functions work

			(void DebugV3())



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

#define E_VEC3 Vector3{FLT_EPSILON, FLT_EPSILON, FLT_EPSILON}


namespace JTL
{

	__declspec(align(16)) struct Vector3
	{
		union
		{
			float v[3];
			struct { float x, y, z; };
			Vector2 xy;
		};

#pragma region BinaryOperators

		Vector3& operator+= (const Vector3 &rhs);

		Vector3& operator-= (const Vector3 &rhs);

		Vector3& operator*= (const float   &rhs);

		Vector3& operator/= (const float   &rhs);


		Vector3  operator+  (const Vector3 &rhs) const;

		Vector3  operator-  (const Vector3 &rhs) const;

		Vector3  operator*  (const float   &rhs) const;

		Vector3  operator/  (const float   &rhs) const;


		bool operator==     (const Vector3 &rhs) const;

		bool operator!=		(const Vector3 &rhs) const;

		bool operator<		(const Vector3 &rhs) const;

		bool operator>		(const Vector3 &rhs) const;

		bool operator<=		(const Vector3 &rhs) const;

		bool operator>=		(const Vector3 &rhs) const;

#pragma endregion

#pragma region UnaryOperators

		float &operator[](unsigned i);

		float  operator[](unsigned i) const;


		Vector3& operator-() const;

#pragma endregion

		void normalize();

	};

#pragma region VectorFunctionHeaders

		float    dot    (const Vector3 &a, const Vector3 &b);

		float    mag    (const Vector3 &v);

		Vector3  normal (const Vector3 &v);

		Vector3  cross  (const Vector3 &a, const Vector3 &b);

		Vector3  lerp   (const Vector3 &a, const Vector3 &b, const float &alpha);

		Vector3  clamp  (const Vector3 &a, const Vector3 &min, const Vector3 &max);

		Vector3  min    (const Vector3 *pts, size_t n);

		Vector3  max    (const Vector3 *pts, size_t n);

		Vector3  reflect(const Vector3 &incident, const Vector3 &normal);

#pragma endregion

}