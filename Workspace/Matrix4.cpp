#include "Matrix3.h"
#include "Matrix4.h"

namespace JTL
{
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

	Matrix4 inverse	   (const Matrix4 &a)
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


	void	   DebugM4()
	{
		assert((ID_MAT4 * ID_MAT4) == ID_MAT4);

		assert(determinant(ID_MAT4) == 1);

		assert(inverse(ID_MAT4) == ID_MAT4);

		assert(transpose(ID_MAT4) == ID_MAT4);
	}
}