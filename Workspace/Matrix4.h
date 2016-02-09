#pragma once

#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3.h"

#define ID_MAT4 Matrix4{ 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 }

namespace JTL
{

	__declspec(align(32)) struct Matrix4
	{
		union
		{
			float m[16], mm[4][4];
		};

#pragma region BinaryOperators

		
		 
		Matrix4& operator += (const Matrix4 &rhs)
		{
			return *this = Matrix4{
				m[0] + rhs.m[0],  m[1] + rhs.m[1] ,  m[2] + rhs.m[2] ,  m[3] + rhs.m[3]  ,
				m[4] + rhs.m[4],  m[5] + rhs.m[5] ,  m[6] + rhs.m[6] ,  m[7] + rhs.m[7]  ,
				m[8] + rhs.m[8],  m[9] + rhs.m[9] ,  m[10] + rhs.m[10],  m[11] + rhs.m[11] ,
				m[12] + rhs.m[12], m[13] + rhs.m[13],  m[14] + rhs.m[14],  m[15] + rhs.m[15] };
		}

		Matrix4& operator -= (const Matrix4 &rhs)
		{
			return *this = Matrix4{
				m[0] - rhs.m[0] ,  m[1] - rhs.m[1] ,  m[2] - rhs.m[2] ,  m[3] - rhs.m[3]  ,
				m[4] - rhs.m[4] ,  m[5] - rhs.m[5] ,  m[6] - rhs.m[6] ,  m[7] - rhs.m[7]  ,
				m[8] - rhs.m[8] ,  m[9] - rhs.m[9] ,  m[10] - rhs.m[10],  m[11] - rhs.m[11] ,
				m[12] - rhs.m[12],  m[13] - rhs.m[13],  m[14] - rhs.m[14],  m[15] - rhs.m[15] };
		}

		Matrix4& operator *= (const Matrix4 &rhs)
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

		Matrix4& operator *= (const Vector4 &rhs)
		{
			return *this *= Matrix4{ rhs.x,0,0,0,
									 rhs.y,0,0,0,
									 rhs.z,0,0,0,
									 rhs.w,0,0,0 };
		}


		Matrix4  operator +  (const Matrix4 &rhs) const
		{
			Matrix4 result = *this;
			result += rhs;
			return result;
		}

		Matrix4  operator -  (const Matrix4 &rhs) const
		{
			Matrix4 result = *this;
			result -= rhs;
			return result;
		}

		Matrix4  operator *  (const Matrix4 &rhs) const
		{
			Matrix4 result = *this;
			result *= rhs;
			return result;
		}

		Matrix4  operator *  (const Vector4 &rhs) const
		{
			Matrix4 result = *this;
			result *= rhs;
			return result;
		}


		bool     operator == (const Matrix4 &rhs) const
		{
			return m[0] == rhs.m[0], m[1] == rhs.m[1], m[2] == rhs.m[2], m[3] == rhs.m[3],
				m[4] == rhs.m[4], m[5] == rhs.m[5], m[6] == rhs.m[6], m[7] == rhs.m[7],
				m[8] == rhs.m[8], m[9] == rhs.m[9], m[10] == rhs.m[10], m[11] == rhs.m[11],
				m[12] == rhs.m[12], m[13] == rhs.m[13], m[14] == rhs.m[14], m[15] == rhs.m[15];
		}

#pragma endregion

	};

#pragma region FunctionHeaders

	float   determinant(const Matrix4 &a);

	Matrix4 inverse(const Matrix4 &a);

	Matrix4 transpose(const Matrix4 &a);

	Matrix4 matrix3To4(const Matrix3 &a);

#pragma endregion

}