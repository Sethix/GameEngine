#define GLEW_STATIC

#include "glew.h"
#include "glfw3.h"
#include "Time.h"

namespace JTL
{

	float Time::getTotalTime()
	{
		INIT_ASSERT(Time);
		return previousTime = glfwGetTime();
	}

	float Time::getDeltaTime()
	{
		INIT_ASSERT(Time);
		double pTime = previousTime;
		return glfwGetTime() - pTime;
	}

}