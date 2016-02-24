/******************************************************

-----------------------Matrix2.h-----------------------

	Purpose -
		Contains an array of numbers in a 2X2 grid.



	Functionality -
		Capable of the following,


		* Addition between matrices			
			
			(+, +=)

		* Subtraction between matrices		
		
			(-, -=)

		* Multiplication between matrices	
		
			(*, *=)

		* Multiplication between matrix and vector 2

			(*, *=)

		* Imperfect equality comparison between matrices

			(==)

		* Calculate the determinant of a matrix 2

			(float determinant(Matrix2))

		* Calculate the inverse of a matrix 2

			(Matrix2 inverse(Matrix2))

		* Transpose matrix 2 to diagonally flip the values

			(Matrix2 transpose(Matrix2))

		* Run test cases to make sure all functions work

			(void DebugM2())



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

#define ID_MAT2 Matrix2{ 1,0,0,1}


namespace JTL
{

	__declspec(align(32)) struct Matrix2
	{
		union
		{
			float m[4], mm[2][2];
			Vector2 c[2];
		};

#pragma region BinaryOperators

		Matrix2& operator += (const Matrix2 &rhs);

		Matrix2& operator -= (const Matrix2 &rhs);

		Matrix2& operator *= (const Matrix2 &rhs);


		Matrix2  operator +  (const Matrix2 &rhs) const;

		Matrix2  operator -  (const Matrix2 &rhs) const;

		Matrix2  operator *  (const Matrix2 &rhs) const;

		Vector2  operator *  (const Vector2 &rhs) const;


		bool     operator == (const Matrix2 &rhs) const;

#pragma endregion

	};

#pragma region MatrixFunctionHeaders

		inline float   determinant (const Matrix2 &a);

		inline Matrix2 inverse     (const Matrix2 &a);

		inline Matrix2 transpose   (const Matrix2 &a);

		inline void	   DebugM2     ();

#pragma endregion

}