/******************************************************

-----------------------Asset.h-------------------------

	Purpose -
		To contain all of our asset data in a place
		accessible to the whole program so that we
		may load and draw textures.



	Functionality -
		Capable of the following,


		* Load an image from a file path provided and
		  store it using a name.

			(void loadTexture(const String *&Name, const int &Columns, const int &Rows, const char *path))

		* Return loaded texture data using a name.

			(Texture getTextures(const String&))

		* Draw a texture to the screen in world space using OpenGl.

			(void drawTexture(const String &Name, Shader &, 
							  const Vector4 &Tint, const int &Index, 
							  const Matrix4 &Model, const Matrix4 &View, const Matrix4 &Projection)



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
#include <unordered_map>

namespace JTL
{
#pragma region ForwardDeclarations
	
	class Shader;
	class Mesh;
	class Transform;
	
	struct Matrix4;
	struct Vector4;

#pragma endregion

	class Asset
	{
		Asset() {}
		Mesh *mesh;

	public:

		struct Texture { unsigned _handle; int width, height; unsigned rows, cols; };

		std::unordered_map<std::string, Texture> textures;

		// Load a texture or spritesheet from a path and assign a name.
		void loadTexture(const std::string &name, const unsigned &rows, const unsigned &cols, const char *path);

		// Get our loaded textures by the name given.
		Texture getTextures(const std::string &name);

		// Draw our texture in world space.
		void drawTexture(const std::string & name, Shader &shader, const Vector4 &color, const int &idx,
						 const Matrix4 &model, const Matrix4 &view, const Matrix4 &proj);


		static Asset &instance() { static Asset i; return i; }
	};
}