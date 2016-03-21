// TODO : Clean-up and move to math library as it's more fitting

#include "Asset.h"
#include "Transform.h"
#include "Shader.h"
#include "Mesh.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glew.h"
#include "glfw3.h"
#include <cassert>

namespace JTL
{
	unsigned makeTextureSprite(unsigned w, unsigned h, unsigned depth, const unsigned char *pixels)
	{
		unsigned texture;

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexImage2D(GL_TEXTURE_2D, 0, depth, w, h, 0, depth, GL_UNSIGNED_BYTE, pixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, 0);
		return texture;
	}

	Asset::Texture loadTextureMap(const char* path, unsigned rows, unsigned cols)
	{
		int w, h, f;
		unsigned d = 0;
		auto p = stbi_load(path, &w, &h, &f, STBI_default);

		switch (f)
		{
			case 1: d = GL_RED;	break; 
			case 2: d = GL_RG; break; 
			case 3: d = GL_RGB; break; 
			case 4: d = GL_RGBA; break;
			default: assert(false && "File not found or incorrect format.");
		}

		unsigned td = makeTextureSprite(w, h, d, p);

		stbi_image_free(p);

		return Asset::Texture{ td, w, h, rows, cols };
	}

	void Asset::loadTexture(const std::string & name, const unsigned &rows, const unsigned &cols, const char * path)
	{
		textures[name] = loadTextureMap(path, rows, cols);

		Vertex verts[] = {  Vertex(Vector2{ -(float)textures[name].width / 2,-(float)textures[name].height / 2 }, Vector4{ 0,1,0,1 }),
							Vertex(Vector2{  (float)textures[name].width / 2,-(float)textures[name].height / 2 }, Vector4{ 1,1,0,1 }),
							Vertex(Vector2{  (float)textures[name].width / 2, (float)textures[name].height / 2 }, Vector4{ 1,0,0,1 }),
							Vertex(Vector2{ -(float)textures[name].width / 2, (float)textures[name].height / 2 }, Vector4{ 0,0,0,1 }) };

		mesh = new Mesh(verts, 4);
	}
	Asset::Texture Asset::getTextures(const std::string & name)
	{
		return textures[name];
	}
	void Asset::drawTexture(const std::string & name, Shader &shader, const Vector4 &color, const int &idx,
							const Matrix4 &model, const Matrix4 &view, const Matrix4 &proj)
	{
		shader.Bind();
		mesh->DrawTexture(proj, view, model, color,
						  textures[name].rows,textures[name].cols, idx, 
						  textures[name]._handle);
	}
}