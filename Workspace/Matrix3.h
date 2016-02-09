/******************************************************

-----------------------Matrix3.h-----------------------

	Purpose -
		Contains an array of numbers in a 3X3 grid.



	Functionality -
		Capable of the following,


		* Addition between matrices

			(+, +=)

		* Subtraction between matrices

			(-, -=)

		* Multiplication between matrices

			(*, *=)

		* Multiplication between matrix and vector 3

			(*, *=)

		* Imperfect equality comparison between matrices

			(==)

		* Calculate the determinant of a matrix 3

			(float determinant(Matrix2))

		* Calculate the inverse of a matrix 3

			(Matrix2 inverse(Matrix2))

		* Transpose matrix 3 to diagonally flip the values

			(Matrix2 transpose(Matrix2))

		* Run test cases to make sure all functions work

			(void DebugM3())

		* Scale using a vector 2 value

			(Matrix3


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

#define ID_MAT3 Matrix3{ 1,0,0,0,1,0,0,0,1 }


namespace JTL
{

	struct Vector2;
	struct Vector3;

	__declspec(align(16)) struct Matrix3
	{
		union
		{
			float m[9], mm[3][3];
		};

#pragma region BinaryOperators

		Vector3  operator[](unsigned i) const;
		Vector3 &operator[](unsigned i);

		Vector2 &right();
	

		Matrix3& operator += (const Matrix3 &rhs);

		Matrix3& operator -= (const Matrix3 &rhs);

		Matrix3& operator *= (const Matrix3 &rhs);


		Vector3& operator *= (const Vector3 &rhs);


		Matrix3  operator +  (const Matrix3 &rhs) const;

		Matrix3  operator -  (const Matrix3 &rhs) const;

		Matrix3  operator *  (const Matrix3 &rhs) const;

		Vector3  operator *  (const Vector3 &rhs) const;


		bool     operator == (const Matrix3 &rhs) const;

#pragma endregion

		static Matrix3 rotate(const float &angle);

		static Matrix3 scale(const Vector2 &s);

		static Matrix3 translate(const Vector2 &t);

	};

#pragma region FunctionHeaders

		float   determinant (const Matrix3 &a);

		Matrix3 inverse	    (const Matrix3 &a);

		Matrix3 transpose   (const Matrix3 &a);

#pragma endregion

}