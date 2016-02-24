/******************************************************

-----------------------Vector4.h-----------------------

	Purpose -
		Contains four floating point values.



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

			(float dot(Vector4, Vector4))

		* Calculate the length of a vector

			(float mag(Vector4))

		* Calculate the normal of a vector

			(Vector4 normal(Vector4))

		* Set the a vector to it's normal

			(Vector4 normalize())

		* Interpolate between two vectors using a value from 0-1

			(Vector4 lerp(Vector4(0), Vector4(1), float))

		* Clamp a vector inside a minimum and maximum point

			(Vector4 clamp(Vector4(A), Vector4(MIN), Vector4(MAX));

		* Grab the minimum values from an array of vectors

			(Vector4 min(Vector4*, size_t))

		* Grab the maximum values from an array of vectors

			(Vector4 max(Vector4*, size_t))

		* Run test cases to make sure all functions work

			(void DebugV4())



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

#include "Vector3.h"

#define E_VEC4 Vector4{FLT_EPSILON, FLT_EPSILON, FLT_EPSILON, FLT_EPSILON}


namespace JTL
{

	__declspec(align(32)) struct Vector4
	{
		union
		{
			float v[4];
			struct { float x, y, z, w; };
			struct { float r, g, b, a; };
			struct { Vector3 vector3;  };
		};

#pragma region BinaryOperators

		Vector4& operator+= (const Vector4 &rhs);

		Vector4& operator-= (const Vector4 &rhs);
		
		Vector4& operator*= (const float   &rhs);

		Vector4& operator/= (const float   &rhs);


		Vector4  operator+  (const Vector4 &rhs) const;

		Vector4  operator-  (const Vector4 &rhs) const;

		Vector4  operator*  (const float   &rhs) const;

		Vector4  operator/  (const float   &rhs) const;


		bool operator==     (const Vector4 &rhs) const;

		bool operator!=		(const Vector4 &rhs) const;

		bool operator<		(const Vector4 &rhs) const;

		bool operator>		(const Vector4 &rhs) const;

		bool operator<=		(const Vector4 &rhs) const;

		bool operator>=		(const Vector4 &rhs) const;

#pragma endregion

#pragma region UnaryOperators

		float &operator[](unsigned i);

		float  operator[](unsigned i) const;


		Vector4  operator-() const;

#pragma endregion

		void normalize();

	};

#pragma region VectorFunctionHeaders

		float    dot    (const Vector4 &a, const Vector4 &b);

		float    mag    (const Vector4 &v);

		Vector4  normal (const Vector4 &v);

		Vector4  lerp   (const Vector4 &a, const Vector4 &b, const float &alpha);

		Vector4  clamp  (const Vector4 &a, const Vector4 &min, const Vector4 &max);

		Vector4  min    (const Vector4 *pts, size_t n);

		Vector4  max    (const Vector4 *pts, size_t n);

#pragma endregion

}
