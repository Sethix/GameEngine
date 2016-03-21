/******************************************************

---------------------Transform.h-----------------------

	Purpose -
		To provide a container representing the objects
		translation, rotation, scale and parenting info.



	Functionality -
		Capable of the following,


		* Return a matrix containing our position, rotation,
		  and scale in world space.

			(Matrix3 getGlobalTransform() const)

		* Return our globalTransform as a matrix4 for drawing.

			(Matrix4 getDrawMatrix() const)

		* Set our parent transform to attach this transform to.

			(void setParent(Transform*))

		* Set our position.

			(void setPosition(Vector2&))

		* Set our scale.

			(void setScale(Vector2&))

		* Set our rotation in radians.

			(void setAngle(float&))

		* Get our position.

			(Vector2 getPosition() const)

		* Get our scale.

			(Vector2 getScale() const)

		* Get our rotation in radians.

			(float getAngle() const)

		* Get the vector to our right locally.

			(Vector2 getRight() const)

		* Get the vector to our up locally.

			(Vector2 getUp() const)



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
#include "Vector4.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "ComponentData.h"
#include <list>

namespace JTL
{
	class Transform : public ComponentData<Transform>
	{
		Transform *parent;
		std::list<Transform*> children;
		Vector2 position, scale;
		float angle;

	public:
		Transform();
		~Transform();

		// Get our global transformation matrix.
		Matrix3 getGlobalTransform() const;

		// Get our global transformation matrix as a matrix4.
		Matrix4 getDrawMatrix() const;


		// Set our parent object. Child object are locked to the transform of a parent.
		void setParent(Transform *);

		// Set our position relative to our origin. If we have no parent our origin is 0,0.
		void setPosition(const Vector2 &);

		// Set our X and Y scale.
		void setScale(const Vector2 &);

		// Set our rotation in radians. For degrees use the macro in JMath.
		void setAngle(float);


		// Return our current position.
		Vector2 getPosition() const;

		// Return our current scale.
		Vector2 getScale() const;

		// Return our current angle in radians.
		float   getAngle() const;

		// Get the vector to our right locally.
		Vector2 getRight() const;

		// Get the vector to our up locally.
		Vector2 getUp() const;
	};
}