/******************************************************

---------------------Rigidbody.h-----------------------

	Purpose -
		To provide a container for physics data 
		to be used in translation and rotation.



	Functionality -
		Capable of the following,


		* Addition of force to be used in translation

			(void addForce(const Vector2&))

		* Addition of torque to be used in rotation

			(void addTorque(const float&))

		* Integrate force/torque into current acceleration

			(void integrate(Transform*, float [deltaTime]))



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
#include "Transform.h"
#include "ComponentData.h"

namespace JTL
{
	class Rigidbody : public ComponentData<Rigidbody>
	{
	public:
		Vector2 velocity, acceleration, force, jerk;
		float mass, drag;

		float angularVelocity, angularAcceleration, torque, angularJerk, angularDrag;

		Rigidbody();

		// Add force determining acceleration at next integration.
		void addForce(const Vector2 &);

		// Add torque for determining angular acceleration at next integration.
		void addTorque(const float &);

		// Integrate force and torque to change our velocity/angular velocity.
		void integrate(Transform *, float dt);
	};
}