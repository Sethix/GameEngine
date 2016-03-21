/******************************************************

------------------------Mesh.h-------------------------

	Purpose -
		To contain vertex and mesh information to
		be used in creating images with OpenGL.



	Functionality -
		Capable of the following,


		* Draw a texture to the screen in world space.
		  For non world space, set the view as an identity matrix.
		  Supports animation using sprite sheets.

			(void drawTexture(const Matrix4 &Projection, const Matrix4 &View, const Matrix4 &Model,
							  const Vector4 &Tint, const int &Rows, const int &Columns,
							  const int &Index, const unsigned &Texture))

		* Drawing primitive shapes. 

			-Disclaimer- This was used as a way to learn OpenGL. It's not very good.

			(void DebugDraw(const Matrix4&))



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
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

namespace JTL
{
	struct Vertex
	{
	public:
		Vertex(const Vector2& vec, const Vector4& color)
		{
			pos.x = vec.x;
			pos.y = vec.y;
			pos.z = 0;
			pos.w = 1;
			col = color;
		}

		Vertex(const Vector3& vec, const Vector4& color)
		{
			pos.x = vec.x;
			pos.y = vec.y;
			pos.z = vec.z;
			pos.w = 1;
			col = color;
		}

		Vertex(const Vector4& vec, const Vector4& color)
		{
			pos = vec;
			col = color;
		}

	private:
		Vector4 pos;
		Vector4 col;
	};

	class Mesh
	{
	public:
		Mesh(const Vertex* verts, const unsigned int &n, unsigned int dType = 999);
		~Mesh();

		// Not very good! My first attempt at drawing with OpenGL.
		void DebugDraw(const Matrix4 &mat);

		// Used in drawing textures in world space.
		void DrawTexture(const Matrix4 &proj, const Matrix4 &view, const Matrix4 &model,
						 const Vector4 &color, const int &rows, const int &cols,
						 const int &idx, const unsigned &texture);

	private:

		enum
		{
			e_POSITION,
			e_ELEMENT,
			NUMBUFFERS
		};

		unsigned int drawCount, drawType, VAO, VBO[NUMBUFFERS];
	};
}