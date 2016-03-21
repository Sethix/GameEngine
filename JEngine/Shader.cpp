// TODO : Clean-up

#include "Shader.h"
#include "ShaderLoader.h"
#include "glew.h"
#include "glfw3.h"

#include <iostream>

namespace JTL
{

	GLuint CreateShader(const char* ss,/* const unsigned long ssLen,*/ GLenum shaderType);

	Shader::Shader()
	{
		program = glCreateProgram();

		shaders[0] = CreateShader(DEBUG_VERT, GL_VERTEX_SHADER);
		shaders[1] = CreateShader(DEBUG_FRAG, GL_FRAGMENT_SHADER);

		glAttachShader(program, shaders[0]);
		glAttachShader(program, shaders[1]);

		glLinkProgram(program);
	}

	Shader::Shader(const char* vert, const char* frag, const bool &fPath)
	{
		program = glCreateProgram();
		if (fPath)
		{
			char* vs;
			char* fs;
			unsigned long vsLen = 0, fsLen = 0;

			loadShader(vert, &vs, vsLen);
			loadShader(frag, &fs, fsLen);

			shaders[0] = CreateShader(vs, GL_VERTEX_SHADER);
			shaders[1] = CreateShader(fs, GL_FRAGMENT_SHADER);
		}
		else
		{
			shaders[0] = CreateShader(vert, GL_VERTEX_SHADER);
			shaders[1] = CreateShader(frag, GL_FRAGMENT_SHADER);
		}
		glAttachShader(program, shaders[0]);
		glAttachShader(program, shaders[1]);

		//glBindAttribLocation(program, 0, "position");
		//glBindFragDataLocation(program, 0, "color");

		glLinkProgram(program);
	}

	Shader::~Shader()
	{
		glDetachShader(program, shaders[0]);
		glDetachShader(program, shaders[1]);

		glDeleteShader(shaders[0]);
		glDeleteShader(shaders[1]);

		glDeleteProgram(program);
	}

	GLuint CreateShader(const char* ss, /*const unsigned long ssLen,*/ GLenum shaderType)
	{
		GLuint shader = glCreateShader(shaderType);

		const GLchar* ShaderSource[1] = { ss };
		//GLint ShaderLength[1] = { ssLen };

		glShaderSource(shader, 1, ShaderSource, NULL);
		glCompileShader(shader);

#if _DEBUG
		GLint success = GL_FALSE;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (success != GL_TRUE)
		{
			char buffer[512];
			glGetShaderInfoLog(shader, 512, NULL, buffer);

			std::cerr << "Shader Error!\n" << buffer << "\n";
		}
#endif
		return shader;
	}

	void Shader::Bind()
	{
		glUseProgram(program);
	}
}