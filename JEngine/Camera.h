/******************************************************

-----------------------Camera.h------------------------

	Purpose -
		To set viewport data and return projection data
		so that we may move the camera in 2-D space.



	Functionality -
		Capable of the following,


		* Return view matrix

			(Matrix4 getView())

		* Return projection matrix

			(void getProj())

		* Update and draw everything relative to our camera.

			(void update())



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
#include "ComponentData.h"
#include "Vector3.h"
#include "Matrix4.h"

namespace JTL
{
	class Camera : public ComponentData<Camera>
	{
	public:
		// This can be used to achieve effects such as split screen multiplayer
		// by using multiple camera entities.
		enum SPACE {FULL, TOP_HALF, BOT_HALF, LFT_HALF, RGT_HALF, 
					TL_CORNER, TR_CORNER, BL_CORNER, BR_CORNER, CENTER_SQUARE} space;

		// This allows us to move our camera. It is used in the view matrix.
		Vector3 pos;

		float near = 0.1f;
		float far = 100;
		float fov = 90;

		// Return the view matrix.
		Matrix4 getView();

		// Return the projection matrix.
		Matrix4 getOrtho();
		Matrix4 getPersp();

		// Set our viewport in GL and draw everything.
		void update();
	};
}