#define GLEW_STATIC

#include "glew.h"
#include "glfw3.h"
#include "Time.h"

namespace JTL
{

	float Time::getTotalTime()
	{
		INIT_ASSERT(Time);
		return glfwGetTime();
	}

	float Time::getDeltaTime()
	{
		INIT_ASSERT(Time);
		return getTotalTime() - previousTime;
	}

	bool Time::step()
	{
		previousTime = glfwGetTime();
		INIT_ASSERT(Time); return true;
	}

}