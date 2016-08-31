// TODO : Clean-up

#define GLEW_STATIC

#include "Window.h"
#include "glew.h"
#include "glfw3.h"

namespace JTL
{

	bool Window::init(int Width, int Height, const char* Title, bool resizeable, bool fullscreen)
	{
		isInit = glfwInit();

		/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

		if(resizeable) glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
		else glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		if(fullscreen) window = glfwCreateWindow(Width, Height, Title, glfwGetPrimaryMonitor(), nullptr);
		else window = glfwCreateWindow(Width, Height, Title, nullptr, nullptr);

		glfwMakeContextCurrent(window);

		glewExperimental = GL_TRUE;
		glewInit();
		
		glfwSwapInterval(1);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		//glDisable(GL_CULL_FACE);
		
		//glOrtho(-((int)Width / 2), (int)Width / 2, -((int)Height / 2), (int)Height / 2, 0, 1);
		//
		width = Width;
		height = Height;

		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		return isInit;
	}

	bool Window::step()
	{
		glfwSwapBuffers(window);
		glfwPollEvents();

		glfwGetFramebufferSize(window, &width, &height);
		
		glClearColor(0.06f, 0.0f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);

		return !glfwWindowShouldClose(window) && !exit;
	}

	void Window::term()
	{
		glfwWindowShouldClose(window);
		glfwTerminate();
	}

}