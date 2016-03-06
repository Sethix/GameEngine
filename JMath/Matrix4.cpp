#include <cassert>
#include "Matrix3.h"
#include "Matrix4.h"
#include "Vector4.h"

namespace JTL
{
#pragma region BinaryOperators

	Matrix4& Matrix4::operator += (const Matrix4 &rhs)
	{
		return *this = Matrix4{
			m[0] + rhs.m[0],  m[1] + rhs.m[1] ,  m[2] + rhs.m[2] ,  m[3] + rhs.m[3]  ,
			m[4] + rhs.m[4],  m[5] + rhs.m[5] ,  m[6] + rhs.m[6] ,  m[7] + rhs.m[7]  ,
			m[8] + rhs.m[8],  m[9] + rhs.m[9] ,  m[10] + rhs.m[10],  m[11] + rhs.m[11] ,
			m[12] + rhs.m[12], m[13] + rhs.m[13],  m[14] + rhs.m[14],  m[15] + rhs.m[15] };
	}

	Matrix4& Matrix4::operator -= (const Matrix4 &rhs)
	{
		return *this = Matrix4{
			m[0] - rhs.m[0] ,  m[1] - rhs.m[1] ,  m[2] - rhs.m[2] ,  m[3] - rhs.m[3]  ,
			m[4] - rhs.m[4] ,  m[5] - rhs.m[5] ,  m[6] - rhs.m[6] ,  m[7] - rhs.m[7]  ,
			m[8] - rhs.m[8] ,  m[9] - rhs.m[9] ,  m[10] - rhs.m[10],  m[11] - rhs.m[11] ,
			m[12] - rhs.m[12],  m[13] - rhs.m[13],  m[14] - rhs.m[14],  m[15] - rhs.m[15] };
	}

	Matrix4& Matrix4::operator *= (const Matrix4 &rhs)
	{
		return *this = Matrix4{
			mm[0][0] * rhs.mm[0][0] + mm[0][1] * rhs.mm[1][0] + mm[0][2] * rhs.mm[2][0] + mm[0][3] * rhs.mm[3][0],
			mm[0][0] * rhs.mm[0][1] + mm[0][1] * rhs.mm[1][1] + mm[0][2] * rhs.mm[2][1] + mm[0][3] * rhs.mm[3][1],
			mm[0][0] * rhs.mm[0][2] + mm[0][1] * rhs.mm[1][2] + mm[0][2] * rhs.mm[2][2] + mm[0][3] * rhs.mm[3][2],
			mm[0][0] * rhs.mm[0][3] + mm[0][1] * rhs.mm[1][3] + mm[0][2] * rhs.mm[2][3] + mm[0][3] * rhs.mm[3][3],

			mm[1][0] * rhs.mm[0][0] + mm[1][1] * rhs.mm[1][0] + mm[1][2] * rhs.mm[2][0] + mm[1][3] * rhs.mm[3][0],
			mm[1][0] * rhs.mm[0][1] + mm[1][1] * rhs.mm[1][1] + mm[1][2] * rhs.mm[2][1] + mm[1][3] * rhs.mm[3][1],
			mm[1][0] * rhs.mm[0][2] + mm[1][1] * rhs.mm[1][2] + mm[1][2] * rhs.mm[2][2] + mm[1][3] * rhs.mm[3][2],
			mm[1][0] * rhs.mm[0][3] + mm[1][1] * rhs.mm[1][3] + mm[1][2] * rhs.mm[2][3] + mm[1][3] * rhs.mm[3][3],

			mm[2][0] * rhs.mm[0][0] + mm[2][1] * rhs.mm[1][0] + mm[2][2] * rhs.mm[2][0] + mm[2][3] * rhs.mm[3][0],
			mm[2][0] * rhs.mm[0][1] + mm[2][1] * rhs.mm[1][1] + mm[2][2] * rhs.mm[2][1] + mm[2][3] * rhs.mm[3][1],
			mm[2][0] * rhs.mm[0][2] + mm[2][1] * rhs.mm[1][2] + mm[2][2] * rhs.mm[2][2] + mm[2][3] * rhs.mm[3][2],
			mm[2][0] * rhs.mm[0][3] + mm[2][1] * rhs.mm[1][3] + mm[2][2] * rhs.mm[2][3] + mm[2][3] * rhs.mm[3][3],

			mm[3][0] * rhs.mm[0][0] + mm[3][1] * rhs.mm[1][0] + mm[3][2] * rhs.mm[2][0] + mm[3][3] * rhs.mm[3][0],
			mm[3][0] * rhs.mm[0][1] + mm[3][1] * rhs.mm[1][1] + mm[3][2] * rhs.mm[2][1] + mm[3][3] * rhs.mm[3][1],
			mm[3][0] * rhs.mm[0][2] + mm[3][1] * rhs.mm[1][2] + mm[3][2] * rhs.mm[2][2] + mm[3][3] * rhs.mm[3][2],
			mm[3][0] * rhs.mm[0][3] + mm[3][1] * rhs.mm[1][3] + mm[3][2] * rhs.mm[2][3] + mm[3][3] * rhs.mm[3][3]

		};
	}


	Matrix4  Matrix4::operator +  (const Matrix4 &rhs) const
	{
		Matrix4 result = *this;
		result += rhs;
		return result;
	}

	Matrix4  Matrix4::operator -  (const Matrix4 &rhs) const
	{
		Matrix4 result = *this;
		result -= rhs;
		return result;
	}

	Matrix4  Matrix4::operator *  (const Matrix4 &rhs) const
	{
		Matrix4 result = *this;
		result *= rhs;
		return result;
	}

	Vector4  Matrix4::operator *  (const Vector4 &rhs) const
	{
		return Vector4{ m[0] * m[1] * m[2] * m[3] * rhs.x,
			m[4] * m[5] * m[6] * m[7] * rhs.y,
			m[8] * m[9] * m[10] * m[11] * rhs.z,
			m[12] * m[13] * m[14] * m[15] * rhs.w, };
	}


	bool     Matrix4::operator == (const Matrix4 &rhs) const
	{
		return m[0] == rhs.m[0], m[1] == rhs.m[1], m[2] == rhs.m[2], m[3] == rhs.m[3],
			m[4] == rhs.m[4], m[5] == rhs.m[5], m[6] == rhs.m[6], m[7] == rhs.m[7],
			m[8] == rhs.m[8], m[9] == rhs.m[9], m[10] == rhs.m[10], m[11] == rhs.m[11],
			m[12] == rhs.m[12], m[13] == rhs.m[13], m[14] == rhs.m[14], m[15] == rhs.m[15];
	}

#pragma endregion

	float   determinant (const Matrix4 &a)
	{
		return{ a.mm[0][3] * a.mm[1][2] * a.mm[2][1] * a.mm[3][0] - a.mm[0][2] * a.mm[1][3] * a.mm[2][1] * a.mm[3][0] -
			a.mm[0][3] * a.mm[1][1] * a.mm[2][2] * a.mm[3][0] + a.mm[0][1] * a.mm[1][3] * a.mm[2][2] * a.mm[3][0] +
			a.mm[0][2] * a.mm[1][1] * a.mm[2][3] * a.mm[3][0] - a.mm[0][1] * a.mm[1][2] * a.mm[2][3] * a.mm[3][0] -
			a.mm[0][3] * a.mm[1][2] * a.mm[2][0] * a.mm[3][1] + a.mm[0][2] * a.mm[1][3] * a.mm[2][0] * a.mm[3][1] +
			a.mm[0][3] * a.mm[1][0] * a.mm[2][2] * a.mm[3][1] - a.mm[0][0] * a.mm[1][3] * a.mm[2][2] * a.mm[3][1] -
			a.mm[0][2] * a.mm[1][0] * a.mm[2][3] * a.mm[3][1] + a.mm[0][0] * a.mm[1][2] * a.mm[2][3] * a.mm[3][1] +
			a.mm[0][3] * a.mm[1][1] * a.mm[2][0] * a.mm[3][2] - a.mm[0][1] * a.mm[1][3] * a.mm[2][0] * a.mm[3][2] -
			a.mm[0][3] * a.mm[1][0] * a.mm[2][1] * a.mm[3][2] + a.mm[0][0] * a.mm[1][3] * a.mm[2][1] * a.mm[3][2] +
			a.mm[0][1] * a.mm[1][0] * a.mm[2][3] * a.mm[3][2] - a.mm[0][0] * a.mm[1][1] * a.mm[2][3] * a.mm[3][2] -
			a.mm[0][2] * a.mm[1][1] * a.mm[2][0] * a.mm[3][3] + a.mm[0][1] * a.mm[1][2] * a.mm[2][0] * a.mm[3][3] +
			a.mm[0][2] * a.mm[1][0] * a.mm[2][1] * a.mm[3][3] - a.mm[0][0] * a.mm[1][2] * a.mm[2][1] * a.mm[3][3] -
			a.mm[0][1] * a.mm[1][0] * a.mm[2][2] * a.mm[3][3] + a.mm[0][0] * a.mm[1][1] * a.mm[2][2] * a.mm[3][3] };
	}

	Matrix4 inverse	    (const Matrix4 &a)
	{
		float d = 1 / determinant(a);

		assert(d != 0);

		return  Matrix4{ (a.m[5] * a.m[10] * a.m[15] - a.m[5] * a.m[11] * a.m[14] - a.m[9] * a.m[6] * a.m[15] +
			a.m[9] * a.m[7] * a.m[14] + a.m[13] * a.m[6] * a.m[11] - a.m[13] * a.m[7] * a.m[10]) * d ,

			(-a.m[1] * a.m[10] * a.m[15] + a.m[1] * a.m[11] * a.m[14] + a.m[9] * a.m[2] * a.m[15] -
				a.m[9] * a.m[3] * a.m[14] - a.m[13] * a.m[2] * a.m[11] + a.m[13] * a.m[3] * a.m[10]) * d ,

			(a.m[1] * a.m[6] * a.m[15] - a.m[1] * a.m[7] * a.m[14] - a.m[5] * a.m[2] * a.m[15] +
				a.m[5] * a.m[3] * a.m[14] + a.m[13] * a.m[2] * a.m[7] - a.m[13] * a.m[3] * a.m[6]) * d ,

			(-a.m[1] * a.m[6] * a.m[11] + a.m[1] * a.m[7] * a.m[10] + a.m[5] * a.m[2] * a.m[11] -
				a.m[5] * a.m[3] * a.m[10] - a.m[9] * a.m[2] * a.m[7] + a.m[9] * a.m[3] * a.m[6]) * d ,


			(-a.m[4] * a.m[10] * a.m[15] + a.m[4] * a.m[11] * a.m[14] + a.m[8] * a.m[6] * a.m[15] -
				a.m[8] * a.m[7] * a.m[14] - a.m[12] * a.m[6] * a.m[11] + a.m[12] * a.m[7] * a.m[10]) * d ,

			(a.m[0] * a.m[10] * a.m[15] - a.m[0] * a.m[11] * a.m[14] - a.m[8] * a.m[2] * a.m[15] +
				a.m[8] * a.m[3] * a.m[14] + a.m[12] * a.m[2] * a.m[11] - a.m[12] * a.m[3] * a.m[10]) * d ,

			(-a.m[0] * a.m[6] * a.m[15] + a.m[0] * a.m[7] * a.m[14] + a.m[4] * a.m[2] * a.m[15] -
				a.m[4] * a.m[3] * a.m[14] - a.m[12] * a.m[2] * a.m[7] + a.m[12] * a.m[3] * a.m[6]) * d ,

			(a.m[0] * a.m[6] * a.m[11] - a.m[0] * a.m[7] * a.m[10] - a.m[4] * a.m[2] * a.m[11] +
				a.m[4] * a.m[3] * a.m[10] + a.m[8] * a.m[2] * a.m[7] - a.m[8] * a.m[3] * a.m[6]) * d ,


			(a.m[4] * a.m[9] * a.m[15] - a.m[4] * a.m[11] * a.m[13] - a.m[8] * a.m[5] * a.m[15] +
				a.m[8] * a.m[7] * a.m[13] + a.m[12] * a.m[5] * a.m[11] - a.m[12] * a.m[7] * a.m[9]) * d ,

			(-a.m[0] * a.m[9] * a.m[15] + a.m[0] * a.m[11] * a.m[13] + a.m[8] * a.m[1] * a.m[15] -
				a.m[8] * a.m[3] * a.m[13] - a.m[12] * a.m[1] * a.m[11] + a.m[12] * a.m[3] * a.m[9]) * d ,

			(a.m[0] * a.m[5] * a.m[15] - a.m[0] * a.m[7] * a.m[13] - a.m[4] * a.m[1] * a.m[15] +
				a.m[4] * a.m[3] * a.m[13] + a.m[12] * a.m[1] * a.m[7] - a.m[12] * a.m[3] * a.m[5]) * d ,

			(-a.m[0] * a.m[5] * a.m[11] + a.m[0] * a.m[7] * a.m[9] + a.m[4] * a.m[1] * a.m[11] -
				a.m[4] * a.m[3] * a.m[9] - a.m[8] * a.m[1] * a.m[7] + a.m[8] * a.m[3] * a.m[5]) * d ,


			(-a.m[4] * a.m[9] * a.m[14] + a.m[4] * a.m[10] * a.m[13] + a.m[8] * a.m[5] * a.m[14] -
				a.m[8] * a.m[6] * a.m[13] - a.m[12] * a.m[5] * a.m[10] + a.m[12] * a.m[6] * a.m[9]) * d ,

			(a.m[0] * a.m[9] * a.m[14] - a.m[0] * a.m[10] * a.m[13] - a.m[8] * a.m[1] * a.m[14] +
				a.m[8] * a.m[2] * a.m[13] + a.m[12] * a.m[1] * a.m[10] - a.m[12] * a.m[2] * a.m[9]) * d ,

			(-a.m[0] * a.m[5] * a.m[14] + a.m[0] * a.m[6] * a.m[13] + a.m[4] * a.m[1] * a.m[14] -
				a.m[4] * a.m[2] * a.m[13] - a.m[12] * a.m[1] * a.m[6] + a.m[12] * a.m[2] * a.m[5]) * d ,

			(a.m[0] * a.m[5] * a.m[10] - a.m[0] * a.m[6] * a.m[9] - a.m[4] * a.m[1] * a.m[10] +
				a.m[4] * a.m[2] * a.m[9] + a.m[8] * a.m[1] * a.m[6] - a.m[8] * a.m[2] * a.m[5]) * d };
	}

	Matrix4 transpose   (const Matrix4 &a)
	{
		return Matrix4{ a.mm[0][0], a.mm[1][0], a.mm[2][0], a.mm[3][0] ,
			a.mm[0][1], a.mm[1][1], a.mm[2][1], a.mm[3][1] ,
			a.mm[0][2], a.mm[1][2], a.mm[2][2], a.mm[3][2] ,
			a.mm[0][3], a.mm[1][3], a.mm[2][3], a.mm[3][3] };
	}

	Matrix4 matrix3To4  (const Matrix3 &a)
	{
		return Matrix4{ a.m[0],a.m[1], 0, a.m[2],
						a.m[3],a.m[4], 0, a.m[5],
						0 ,    0 ,     1 ,0,
						a.m[6],a.m[7], 0, a.m[8] };
	}


	void	DebugM4()
	{
		assert((ID_MAT4 * ID_MAT4) == ID_MAT4);

		assert(determinant(ID_MAT4) == 1);

		assert(inverse(ID_MAT4) == ID_MAT4);

		assert(transpose(ID_MAT4) == ID_MAT4);
	}
}