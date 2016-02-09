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

		Matrix2& operator += (const Matrix2 &rhs)
		{
			return *this = Matrix2{	m[0] + rhs.m[0] ,  m[1] + rhs.m[1] ,  
									m[2] + rhs.m[2] ,  m[3] + rhs.m[3] };
		}

		Matrix2& operator -= (const Matrix2 &rhs)
		{
			return *this = Matrix2{ m[0] - rhs.m[0] ,  m[1] - rhs.m[1] ,  
									m[2] - rhs.m[2] ,  m[3] - rhs.m[3] };
		}

		Matrix2& operator *= (const Matrix2 &rhs)
		{
			return *this = Matrix2{ mm[0][0] * rhs.mm[0][0] + mm[0][1] * rhs.mm[1][0],
									mm[0][0] * rhs.mm[0][1] + mm[0][1] * rhs.mm[1][1],

									mm[1][0] * rhs.mm[0][0] + mm[1][1] * rhs.mm[1][0],
									mm[1][0] * rhs.mm[0][1] + mm[1][1] * rhs.mm[1][1] };
		};

		Matrix2& operator *= (const Vector2 &rhs)
		{
			return *this *= Matrix2{ rhs.x, 0,
									 rhs.y, 0 };
		}


		Matrix2  operator +  (const Matrix2 &rhs) const
		{
			Matrix2 result = *this;
			result += rhs;
			return result;
		}

		Matrix2  operator -  (const Matrix2 &rhs) const
		{
			Matrix2 result = *this;
			result -= rhs;
			return result;
		}

		Matrix2  operator *  (const Matrix2 &rhs) const
		{
			Matrix2 result = *this;
			result *= rhs;
			return result;
		}

		Matrix2  operator *  (const Vector2 &rhs) const
		{
			Matrix2 result = *this;
			result *= rhs;
			return result;
		}


		bool     operator == (const Matrix2 &rhs) const
		{
			return c[0] == rhs.c[0] && c[1] == rhs.c[1];
		}

#pragma endregion

	};

#pragma region FunctionHeaders

		inline float   determinant (const Matrix2 &a);

		inline Matrix2 inverse     (const Matrix2 &a);

		inline Matrix2 transpose   (const Matrix2 &a);

		inline void	   DebugM2     ();

#pragma endregion

}