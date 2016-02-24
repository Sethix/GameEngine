/******************************************************

-----------------------Matrix4.h-----------------------

	Purpose -
		Contains an array of numbers in a 4X4 grid.



	Functionality -
		Capable of the following,


		* Addition between matrices

			(+, +=)

		* Subtraction between matrices

			(-, -=)

		* Multiplication between matrices

			(*, *=)

		* Multiplication between matrix and vector 4

			(*, *=)

		* Imperfect equality comparison between matrices

			(==)

		* Calculate the determinant of a matrix 4

			(float determinant(Matrix4))

		* Calculate the inverse of a matrix 4

			(Matrix4 inverse(Matrix4))

		* Transpose matrix 4 to diagonally flip the values

			(Matrix4 transpose(Matrix4))

		* Convert a matrix 3 into a matrix 4

			(Matrix4 matrix3To4(Matrix3))

		* Run test cases to make sure all functions work

			(void DebugM4())



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

#define ID_MAT4 Matrix4{ 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 }


namespace JTL
{

	struct Vector4;

	__declspec(align(32)) struct Matrix4
	{
		union
		{
			float m[16], mm[4][4];
		};

#pragma region BinaryOperators	
		 
		Matrix4& operator += (const Matrix4 &rhs);

		Matrix4& operator -= (const Matrix4 &rhs);

		Matrix4& operator *= (const Matrix4 &rhs);


		Matrix4  operator +  (const Matrix4 &rhs) const;

		Matrix4  operator -  (const Matrix4 &rhs) const;

		Matrix4  operator *  (const Matrix4 &rhs) const;

		Vector4  operator *  (const Vector4 &rhs) const;


		bool     operator == (const Matrix4 &rhs) const;

#pragma endregion

	};

#pragma region MatrixFunctionHeaders

	float   determinant(const Matrix4 &a);

	Matrix4 inverse(const Matrix4 &a);

	Matrix4 transpose(const Matrix4 &a);

	Matrix4 matrix3To4(const Matrix3 &a);

#pragma endregion

}