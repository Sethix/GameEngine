/******************************************************

-----------------------Vector2.h-----------------------

	Purpose -
		Contains two floating point values.



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

			(float dot(Vector2, Vector2))

		* Calculate the length of a vector

			(float mag(Vector2))

		* Convert from a vector to an angle

			(float toAngle(Vector2))

		* Convert from an angle to a vector

			(Vector2 fromAngle(float))

		* Calculate the normal of a vector

			(Vector2 normal(Vector2))

		* Set the a vector to it's normal

			(Vector2 normalize())

		* Interpolate between two vectors using a value from 0-1

			(Vector2 lerp(Vector2(0), Vector2(1), float))

		* Clamp a vector inside a minimum and maximum point

			(Vector2 clamp(Vector2(A), Vector2(MIN), Vector2(MAX));

		* Grab the minimum values from an array of vectors

			(Vector2 min(Vector2*, size_t))

		* Grab the maximum values from an array of vectors

			(Vector2 max(Vector2*, size_t))

		* Calculate the perpendicular of a vector

			(Vector2 perp(Vector2))

		* Calculate physcal reflection off of a normalized surface

			(Vector2 reflect(Vector2 incident, Vector2 normal))

		* Run test cases to make sure all functions work

			(void DebugV2())



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

#define E_VEC2 Vector2{FLT_EPSILON, FLT_EPSILON}


namespace JTL
{

    __declspec(align(32)) struct Vector2
	{
		union
		{
			float v[2];
			struct { float x, y; };
		};

#pragma region BinaryOperators

		Vector2& operator+= (const Vector2 &rhs);
		
		Vector2& operator-= (const Vector2 &rhs);

		Vector2& operator*= (const Vector2 &rhs);

		Vector2& operator/= (const Vector2 &rhs);

		Vector2& operator*= (const float   &rhs);

		Vector2& operator/= (const float   &rhs);


		Vector2  operator+  (const Vector2 &rhs) const;

		Vector2  operator-  (const Vector2 &rhs) const;

		Vector2  operator*  (const Vector2 &rhs) const;

		Vector2  operator/  (const Vector2 &rhs) const;

		Vector2  operator*  (const float   &rhs) const;

		Vector2  operator/  (const float   &rhs) const;


		bool operator==     (const Vector2 &rhs) const;

		bool operator!=     (const Vector2 &rhs) const;

		bool operator<      (const Vector2 &rhs) const;

		bool operator>      (const Vector2 &rhs) const;

		bool operator<=     (const Vector2 &rhs) const;

		bool operator>=     (const Vector2 &rhs) const;

#pragma endregion

#pragma region UnaryOperators

		float &operator[](unsigned idx);

		float  operator[](unsigned idx) const;


		Vector2  operator-() const;

#pragma endregion

		void normalize();

	};

#pragma region VectorFunctionHeaders

	float    dot(const Vector2 &a, const Vector2 &b);

	float    mag(const Vector2 &v);

	float    toAngle(const Vector2 &v);

	Vector2  fromAngle(const float &a);

	Vector2  normal(const Vector2 &v);

	Vector2  lerp(const Vector2 &a, const Vector2 &b, const float &alpha);

	Vector2  clamp(const Vector2 &a, const Vector2 &min, const Vector2 &max);

	Vector2  min(const Vector2 *pts, size_t n);

	Vector2  max(const Vector2 *pts, size_t n);

	Vector2  perp(const Vector2 &a);

	Vector2  reflect(const Vector2 &incident, const Vector2 &normal);

#pragma endregion

}
