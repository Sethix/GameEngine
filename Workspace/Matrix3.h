#pragma once

#include "Matrix2.h"
#include "Vector3.h"

#define ID_MAT3 Matrix3{ 1,0,0,0,1,0,0,0,1 }



namespace JTL
{
	//struct Matrix3;
	//Matrix3 transpose(const Matrix3 &a);
	__declspec(align(16)) struct Matrix3
	{
		union
		{
			float m[9], mm[3][3];
		};

#pragma region BinaryOperators
		//Vector3 &getCol(unsigned i) { return *(Vector3*)mm[i]; }
		// mat[0]
		// mat.c[0]
		Vector3  operator[](unsigned i) const { return *(Vector3*)mm[i]; }
		Vector3 &operator[](unsigned i)		  { return *(Vector3*)mm[i]; }

		Vector2 &right() { return *(Vector2*)mm[0]; }
	

		Matrix3& operator += (const Matrix3 &rhs)
		{
			return *this = Matrix3{
				m[0] + rhs.m[0] , m[1] + rhs.m[1] , m[2] + rhs.m[2] ,  
				m[3] + rhs.m[3] , m[4] + rhs.m[4] , m[5] + rhs.m[5] ,  
				m[6] + rhs.m[6] , m[7] + rhs.m[7] , m[8] + rhs.m[8] };
		}

		Matrix3& operator -= (const Matrix3 &rhs)
		{
			return *this = Matrix3{
				m[0] - rhs.m[0] , m[1] - rhs.m[1] , m[2] - rhs.m[2] ,
				m[3] - rhs.m[3] , m[4] - rhs.m[4] , m[5] - rhs.m[5] ,
				m[6] - rhs.m[6] , m[7] - rhs.m[7] , m[8] - rhs.m[8] };
		}

		Matrix3& operator *= (const Matrix3 &rhs)
		{
			return *this = Matrix3{
				mm[0][0] * rhs.mm[0][0] + mm[0][1] * rhs.mm[1][0] + mm[0][2] * rhs.mm[2][0],
				mm[0][0] * rhs.mm[0][1] + mm[0][1] * rhs.mm[1][1] + mm[0][2] * rhs.mm[2][1],
				mm[0][0] * rhs.mm[0][2] + mm[0][1] * rhs.mm[1][2] + mm[0][2] * rhs.mm[2][2],

				mm[1][0] * rhs.mm[0][0] + mm[1][1] * rhs.mm[1][0] + mm[1][2] * rhs.mm[2][0],
				mm[1][0] * rhs.mm[0][1] + mm[1][1] * rhs.mm[1][1] + mm[1][2] * rhs.mm[2][1],
				mm[1][0] * rhs.mm[0][2] + mm[1][1] * rhs.mm[1][2] + mm[1][2] * rhs.mm[2][2],

				mm[2][0] * rhs.mm[0][0] + mm[2][1] * rhs.mm[1][0] + mm[2][2] * rhs.mm[2][0],
				mm[2][0] * rhs.mm[0][1] + mm[2][1] * rhs.mm[1][1] + mm[2][2] * rhs.mm[2][1],
				mm[2][0] * rhs.mm[0][2] + mm[2][1] * rhs.mm[1][2] + mm[2][2] * rhs.mm[2][2] };
		}


		Vector3& operator *= (const Vector3 &rhs)
		{
			return Vector3{
				m[0] * m[1] * m[2] * rhs.x, // dot(row, vector) for each element
				m[3] * m[4] * m[5] * rhs.y,
				m[6] * m[7] * m[8] * rhs.z
			};
		}


		Matrix3  operator +  (const Matrix3 &rhs) const
		{
			Matrix3 result = *this;
			result += rhs;
			return result;
		}

		Matrix3  operator -  (const Matrix3 &rhs) const
		{
			Matrix3 result = *this;
			result -= rhs;
			return result;
		}

		Matrix3  operator *  (const Matrix3 &rhs) const
		{
			Matrix3 result = *this;
			result *= rhs;
			return result;
		}

		Vector3  operator *  (const Vector3 &rhs) const
		{
			Matrix3 temp = *this;
			Vector3 result = temp *= rhs;
			return result;
		}


		bool     operator == (const Matrix3 &rhs) const
		{
			return  m[0] == rhs.m[0] && m[1] == rhs.m[1] && m[2] == rhs.m[2] && 
					m[3] == rhs.m[3] && m[4] == rhs.m[4] && m[5] == rhs.m[5] && 
					m[6] == rhs.m[6] && m[7] == rhs.m[7] && m[8] == rhs.m[8];
		}

#pragma endregion

		static Matrix3 rotate(const float &angle)
		{
			return	Matrix3{ cos(angle), sin(angle), 0,
							 -sin(angle),  cos(angle), 0,
							 0		   , 0          , 1 };
		}

		static Matrix3 scale(const Vector2 &s)
		{
			return Matrix3{ s.x, 0,   0,
							0  , s.y, 0,
							0  , 0  , 1 };
		}

		static Matrix3 translate(const Vector2 &t)
		{
			return Matrix3{ 1, 0, 0,
							0, 1, 0,
							t.x, t.y, 1 };
		}

	};

#pragma region FunctionHeaders

		float   determinant (const Matrix3 &a);

		Matrix3 inverse	   (const Matrix3 &a);

		//Matrix3 transpose   (const Matrix3 &a);

#pragma endregion

}