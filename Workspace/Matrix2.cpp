#include <cassert>
#include "Matrix2.h"
#include "Vector2.h"

namespace JTL
{
#pragma region BinaryOperators

	Matrix2& Matrix2::operator += (const Matrix2 &rhs)
	{
		return *this = Matrix2{ m[0] + rhs.m[0] ,  m[1] + rhs.m[1] ,
								m[2] + rhs.m[2] ,  m[3] + rhs.m[3] };
	}

	Matrix2& Matrix2::operator -= (const Matrix2 &rhs)
	{
		return *this = Matrix2{ m[0] - rhs.m[0] ,  m[1] - rhs.m[1] ,
			m[2] - rhs.m[2] ,  m[3] - rhs.m[3] };
	}

	Matrix2& Matrix2::operator *= (const Matrix2 &rhs)
	{
		return *this = Matrix2{ mm[0][0] * rhs.mm[0][0] + mm[0][1] * rhs.mm[1][0],
								mm[0][0] * rhs.mm[0][1] + mm[0][1] * rhs.mm[1][1],

								mm[1][0] * rhs.mm[0][0] + mm[1][1] * rhs.mm[1][0],
								mm[1][0] * rhs.mm[0][1] + mm[1][1] * rhs.mm[1][1] };
	};

	Vector2& Matrix2::operator *= (const Vector2 &rhs)
	{
		return *this *= Vector2{ m[0] * m[1] * rhs.x,
								 m[2] * m[3] * rhs.y };
	}


	Matrix2  Matrix2::operator +  (const Matrix2 &rhs) const
	{
		Matrix2 result = *this;
		result += rhs;
		return result;
	}

	Matrix2  Matrix2::operator -  (const Matrix2 &rhs) const
	{
		Matrix2 result = *this;
		result -= rhs;
		return result;
	}

	Matrix2  Matrix2::operator *  (const Matrix2 &rhs) const
	{
		Matrix2 result = *this;
		result *= rhs;
		return result;
	}

	Vector2  Matrix2::operator *  (const Vector2 &rhs) const
	{
		Matrix2 temp = *this;
		Vector2 result = temp *= rhs;
		return result;
	}


	bool     Matrix2::operator == (const Matrix2 &rhs) const
	{
		return c[0] == rhs.c[0] && c[1] == rhs.c[1];
	}

#pragma endregion

	float   determinant (const Matrix2 &a)
	{
		return a.m[0] * a.m[3] - a.m[1] * a.m[2];
	}

	Matrix2 inverse	   (const Matrix2 &a)
	{
		float d = 1 / determinant(a);
		return{ a.m[0] * d ,a.m[1] * d ,a.m[2] * d ,a.m[3] * d };
	}

	Matrix2 transpose   (const Matrix2 &a)
	{
		return{ a.m[0], a.m[2], a.m[1], a.m[3] };
	}


	void    DebugM2()
	{
		assert((ID_MAT2 * ID_MAT2) == ID_MAT2);

		assert(determinant(ID_MAT2) == 1);

		assert(inverse(ID_MAT2) == ID_MAT2);

		assert(transpose(ID_MAT2) == ID_MAT2);
	}
}
