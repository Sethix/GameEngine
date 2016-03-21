// TODO : Re-build this class. Kind of bad.
// Served it's purpose and taught me openGL.

/******************************************************

---------------------DebugDraw.h-----------------------

	Purpose -
		To display a visual representation of entity
		data such as colliders for testing purposes.



	Functionality -
		Capable of the following,


		* Draw Collider, Transform or Rigidbody on the screen.

			(void draw(const Transform&, const Rigidbody&, const Matrix4&))

			(void draw(const Transform&, const Matrix4&))



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
#include "System.h"
#include "Shader.h"
#include "Mesh.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "Vector4.h"

#define SHAPECOLOR Vector4{0.4f, 0.2f, 0.6f, 1.0f}

namespace JTL
{
	class DebugDraw
	{
		Shader shader;
		Mesh *mesh;
		bool isRigidBody;
	public:
		DebugDraw(const Transform &tform);
		DebugDraw(const Rigidbody &rbody);
		DebugDraw(const Collider &coll);
		~DebugDraw();
		void draw(const Transform &tform, const Matrix4 &proj);
		void draw(const Transform &tform, const Rigidbody &rBody, const Matrix4 &proj);
	};
}