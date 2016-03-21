/******************************************************

------------------------Shader.h-----------------------

	Purpose -
		Contains shader programs with vertex
		and fragment shaders to be used with OpenGL.



	Functionality -
		Capable of the following,


		* Bind the shader so that mesh's use it for drawing. 

			(void Bind())



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

namespace JTL
{

	class Shader
	{
	public:
		// You can use the default shader with the default constructor.
		// If you would prefer you can load in shaders yourself.
		// Set fPath to true if it's a file path or false if it's a source string.
		Shader();
		Shader(const char* vertLoc, const char* fragLoc, const bool &fPath);
		~Shader();

		// Bind the program.
		void Bind();

	private:
		unsigned int program, shaders[2];
	};
}