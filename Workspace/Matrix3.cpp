#include "Matrix3.h"

namespace JTL
{
	float   determinant (const Matrix3 &a)
	{
		return{ a.mm[0][0] * a.mm[1][1] * a.mm[2][2] + a.mm[0][1] * a.mm[1][2] * a.mm[2][0] +
			a.mm[0][2] * a.mm[1][0] * a.mm[2][1] - a.mm[0][0] * a.mm[1][2] * a.mm[2][1] -
			a.mm[0][1] * a.mm[1][0] * a.mm[2][2] - a.mm[0][2] * a.mm[1][1] * a.mm[2][0] };
	}

	Matrix3 inverse	   (const Matrix3 &a)
	{
		float d = 1 / determinant(a);

		assert(d != 0);

		return{ (a.mm[1][1] * a.mm[2][2] - a.mm[2][1] * a.mm[1][2]) * d,
			(a.mm[0][2] * a.mm[2][1] - a.mm[0][1] * a.mm[2][2]) * d,
			(a.mm[0][1] * a.mm[1][2] - a.mm[0][2] * a.mm[1][1]) * d,

			(a.mm[1][2] * a.mm[2][0] - a.mm[1][0] * a.mm[2][2]) * d,
			(a.mm[0][0] * a.mm[2][2] - a.mm[0][2] * a.mm[2][0]) * d,
			(a.mm[1][0] * a.mm[0][2] - a.mm[0][0] * a.mm[1][2]) * d,

			(a.mm[1][0] * a.mm[2][1] - a.mm[2][0] * a.mm[1][1]) * d,
			(a.mm[2][0] * a.mm[0][1] - a.mm[0][0] * a.mm[2][1]) * d,
			(a.mm[0][0] * a.mm[1][1] - a.mm[1][0] * a.mm[0][1]) * d };
	}

	Matrix3 transpose   (const Matrix3 &a)
	{
		return Matrix3{ a.mm[0][0], a.mm[1][0], a.mm[2][0],
			a.mm[0][1], a.mm[1][1], a.mm[2][1],
			a.mm[0][2], a.mm[1][2], a.mm[2][2] };
	}


	inline void	   DebugM3()
	{
		assert((ID_MAT3 * ID_MAT3) == ID_MAT3);

		assert(determinant(ID_MAT3) == 1);

		assert(inverse(ID_MAT3) == ID_MAT3);

		assert(transpose(ID_MAT3) == ID_MAT3);
	}
}