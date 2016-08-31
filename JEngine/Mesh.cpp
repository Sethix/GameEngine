// TODO : Clean-up

#include <cassert>
#include "Asset.h"
#include "Matrix4.h"
#include "glew.h"
#include "glfw3.h"

namespace JTL
{
	Mesh::Mesh(const Vertex* verts, const unsigned int &n, unsigned int dType)
	{
		GLuint *elements = nullptr;
		if (n >= 3)
		{
			tCount = (n - 2) * 3;

			if(dType == 999) drawType = GL_TRIANGLES;
			else drawType = dType;

			elements = new GLuint[tCount];

			int tempCounter = 0;

			elements[0] = 0;
			elements[1] = 1;
			elements[2] = 2;

			for (unsigned i = 3; i < tCount; ++i)
			{
				if (i % 3 == 0)
				{
					elements[i] = 0;
					tempCounter += 2;
				}
				else elements[i] = i - tempCounter;
			}
		}
		else if (n == 2)
		{
			tCount = 2;
			if (dType == 999) drawType = GL_LINES;
			else drawType = dType;

			elements = new GLuint[tCount];

			elements[0] = 0;
			elements[1] = 1;
		}
		else if (n == 1)
		{
			tCount = 1;
			if (dType == 999) drawType = GL_POINT;
			else drawType = dType;

			elements = new GLuint[tCount];

			elements[0] = 0;

		}
		
		assert(n > 0);

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(NUMBUFFERS, VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO[e_POSITION]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*n, verts, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[e_ELEMENT]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * tCount, elements, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector4)));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		
		vCount = n;

		delete[] elements;
	}

	Mesh::Mesh(const Vertex *verts, const unsigned *atris, const unsigned &vsize, const unsigned &tsize)
	{
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(NUMBUFFERS, VBO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO[e_POSITION]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vsize, verts, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[e_ELEMENT]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * tsize, atris, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Vector4)));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		vCount = vsize;
		tCount = tsize;
	}
	
	Mesh::Mesh()
	{

	}

	Mesh::~Mesh()
	{
		//glDeleteBuffers(1, &VBO[e_POSITION]);
		//glDeleteBuffers(1, &VBO[e_ELEMENT]);
		//glDeleteVertexArrays(1, &VAO);
	}

	void Mesh::DebugDraw(const Matrix4 &mat)
	{
		glBindVertexArray(VAO);

		glUniformMatrix4fv(2, 1, GL_TRUE, mat.m);

		glDrawElements(drawType, tCount, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}

	void Mesh::DrawTexture(const Matrix4 &proj, const Matrix4 &view, const Matrix4 &model, 
						   const Vector4 &color, const int &rows, const int &cols, 
						   const int &idx, const unsigned &texture)
	{
		glBindVertexArray(VAO);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glUniform4fv(2, 1, color.v);
		
		glUniformMatrix4fv(3, 1, GL_TRUE, model.m);
		glUniformMatrix4fv(4, 1, GL_TRUE, view.m);
		glUniformMatrix4fv(5, 1, GL_TRUE, proj.m);
		
		glUniform1i(6, rows);
		glUniform1i(7, cols);
		glUniform1i(8, idx);

		glUniform1i(9, 0);

		glDrawElements(drawType, tCount, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}
}