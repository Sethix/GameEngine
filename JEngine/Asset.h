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
#include <Matrix4.h>
#include <Matrix3.h>
#include <Vector4.h>
#include <Vector3.h>
#include <Vector2.h>

namespace JTL
{

#pragma region AssetTypes

	class Mesh
	{
	public:

		struct Vertex
		{
		public:
			Vertex()
			{
				pos = { 0,0,0,0 };
				col = { 0,0,0,0 };
			}
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

			enum
			{
				POSITION = 0,
				COLOR = 16
			};

//		private:
			Vector4 pos;
			Vector4 col;
		};

		Mesh(const Vertex* verts, const unsigned int &n, unsigned int dType = 999);
		Mesh(const Vertex *, const unsigned *, const unsigned &, const unsigned &);
		Mesh();
		~Mesh();

		// Not very good! My first attempt at drawing with OpenGL.
		void DebugDraw(const Matrix4 &mat);

		// Used in drawing textures in world space.
		void DrawTexture(const Matrix4 &proj, const Matrix4 &view, const Matrix4 &model,
			const Vector4 &color, const int &rows, const int &cols,
			const int &idx, const unsigned &texture);

		enum
		{
			e_POSITION,
			e_ELEMENT,
			NUMBUFFERS
		};

		unsigned int tris, vCount, tCount, drawType, VAO, VBO[NUMBUFFERS];
	};

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

	struct Texture { unsigned _handle; int width, height; unsigned rows, cols; };

#pragma endregion

#pragma region ForwardDeclarations
	
	class Transform;

#pragma endregion

	class Asset
	{
		Asset() {}
		//Mesh *mesh;

	public:		

		std::unordered_map<std::string, Texture> textures;
		std::unordered_map<std::string, Mesh> meshes;

		// Load a texture or spritesheet from a path and assign a name.
		void loadTexture(const std::string &name, const unsigned &rows, const unsigned &cols, const char *path);

		// Get our loaded textures by the name given.
		Texture getTextures(const std::string &name);

		// Draw our texture in world space.
		void drawTexture(const std::string & name, Shader &shader, const Vector4 &color, const int &idx,
						 const Matrix4 &model, const Matrix4 &view, const Matrix4 &proj);

		void loadMesh(const std::string &name, const char *path);

		Mesh getMesh(const std::string &name);

		void drawMesh(const std::string &name, Shader &shader, const Vector4 &color,
					  const Matrix4 &model, const Matrix4 &view, const Matrix4 &proj);


		static Asset &instance() { static Asset i; return i; }
	};
}