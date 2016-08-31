// TODO : Clean-up and move to math library as it's more fitting

#include "Asset.h"
#include "Transform.h"
#include "Shader.h"
#include "Mesh.h"
#define STB_IMAGE_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION 
#include "tiny_obj_loader.h"
#include <random>
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

	Texture loadTextureMap(const char* path, unsigned rows, unsigned cols)
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

		return Texture{ td, w, h, rows, cols };
	}

	void Asset::loadTexture(const std::string & name, const unsigned &rows, const unsigned &cols, const char * path)
	{
		textures[name] = loadTextureMap(path, rows, cols);

		Mesh::Vertex verts[] = { Mesh::Vertex(Vector2{ -(float)textures[name].width / 2,-(float)textures[name].height / 2 }, Vector4{ 0,1,0,1 }),
			Mesh::Vertex(Vector2{  (float)textures[name].width / 2,-(float)textures[name].height / 2 }, Vector4{ 1,1,0,1 }),
			Mesh::Vertex(Vector2{  (float)textures[name].width / 2, (float)textures[name].height / 2 }, Vector4{ 1,0,0,1 }),
			Mesh::Vertex(Vector2{ -(float)textures[name].width / 2, (float)textures[name].height / 2 }, Vector4{ 0,0,0,1 }) };

		meshes[name] = Mesh(verts, 4);
	}
	Texture Asset::getTextures(const std::string & name)
	{
		return textures[name];
	}
	void Asset::drawTexture(const std::string & name, Shader &shader, const Vector4 &color, const int &idx,
							const Matrix4 &model, const Matrix4 &view, const Matrix4 &proj)
	{
		shader.Bind();
		meshes[name].DrawTexture(proj, view, model, color,
						  textures[name].rows,textures[name].cols, idx, 
						  textures[name]._handle);
	}

	void Asset::loadMesh(const std::string & name, const char * path)
	{
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string err;

		bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);

		Mesh::Vertex   *verts = new Mesh::Vertex[attrib.vertices.size() / 3];
		unsigned * tris = new unsigned[shapes[0].mesh.indices.size()];

		for (int i = 0; i < attrib.vertices.size() / 3; ++i)
		{
			verts[i] = Mesh::Vertex(Vector4{ attrib.vertices[i * 3],
						  attrib.vertices[i * 3 + 1],
						  attrib.vertices[i * 3 + 2],
						  1.0f },
						  Vector4 { 1.0,1.0,1.0,1.0 });

			verts[i].col[0] = rand() * 1.0f / RAND_MAX;
			verts[i].col[1] = rand() * 1.0f / RAND_MAX;
			verts[i].col[2] = rand() * 1.0f / RAND_MAX;
			verts[i].col[3] = 1;
		}

		for (int i = 0; i < shapes[0].mesh.indices.size(); ++i)
			tris[i] = shapes[0].mesh.indices[i].vertex_index;

		Mesh retval = Mesh(verts, tris, attrib.vertices.size() / 3, shapes[0].mesh.indices.size());

		delete[] verts;
		delete[] tris;
		// then we can call makeGeometry as per normal.
		meshes[name] = retval;

	}
	Mesh Asset::getMesh(const std::string & name)
	{
		return meshes[name];
	}
	void Asset::drawMesh(const std::string & name, Shader & shader, const Vector4 & color, const Matrix4 & model, const Matrix4 & view, const Matrix4 & proj)
	{
		shader.Bind();

		// binding the VAO also binds the IBO (tri) and VBO (verts)
		glBindVertexArray(meshes[name].VAO);

		glUniformMatrix4fv(2, 1, GL_TRUE, model.m);
		glUniformMatrix4fv(3, 1, GL_TRUE, view.m);
		glUniformMatrix4fv(4, 1, GL_TRUE, proj.m);

		// Draw elements will draw the vertices that are currently bound
		// using an array of indices.
		// IF AN IBO IS BOUND, we don't need to provide any indices.
		glDrawElements(GL_TRIANGLES, meshes[name].tCount, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
		
	}
}