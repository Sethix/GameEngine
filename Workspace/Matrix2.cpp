#include "Matrix2.h"

namespace JTL
{
	inline float   determinant (const Matrix2 &a)
	{
		return a.m[0] * a.m[3] - a.m[1] * a.m[2];
	}

	inline Matrix2 inverse	   (const Matrix2 &a)
	{
		float d = 1 / determinant(a);
		return{ a.m[0] * d ,a.m[1] * d ,a.m[2] * d ,a.m[3] * d };
	}

	inline Matrix2 transpose   (const Matrix2 &a)
	{
		return{ a.m[0], a.m[2], a.m[1], a.m[3] };
	}


	inline void    DebugM2()
	{
		assert((ID_MAT2 * ID_MAT2) == ID_MAT2);

		assert(determinant(ID_MAT2) == 1);

		assert(inverse(ID_MAT2) == ID_MAT2);

		assert(transpose(ID_MAT2) == ID_MAT2);
	}
}
