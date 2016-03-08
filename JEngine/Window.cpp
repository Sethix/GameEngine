#define GLEW_STATIC

#include "Window.h"
#include "glew.h"
#include "glfw3.h"

namespace JTL
{

	bool Window::init(unsigned Width, unsigned Height, const char* Title, bool resizeable, bool fullscreen)
	{
		isInit = glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		if(resizeable) glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		else glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		if(fullscreen) window = glfwCreateWindow(Width, Height, Title, glfwGetPrimaryMonitor(), nullptr);
		else window = glfwCreateWindow(Width, Height, Title, nullptr, nullptr);

		glfwMakeContextCurrent(window);

		glewExperimental = GL_TRUE;
		glewInit();

		width = Width;
		height = Height;

		return isInit;
	}

	bool Window::step()
	{
		glfwSwapBuffers(window);
		glfwPollEvents();

		return !glfwWindowShouldClose(window) && !exit;
	}

	void Window::term()
	{
		glfwWindowShouldClose(window);
		glfwTerminate();
	}

}