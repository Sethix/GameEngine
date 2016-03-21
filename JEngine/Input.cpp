// TODO : Clean-up(?)

#define GLEW_STATIC

#include "Input.h"
#include "Window.h"
#include "glew.h"
#include "glfw3.h"
#include <cstring>

namespace JTL
{

	bool Input::init()
	{
		memset(keyRelease, 0, NUM_OF_KEYS);
		memset(keyPress, 0, NUM_OF_KEYS);
		memset(mouseRelease, 0, NUM_OF_MOUSE_BTNS);
		memset(mousePress, 0, NUM_OF_MOUSE_BTNS);
		memset(joyRelease, 0, NUM_OF_JOY_BTNS * NUM_OF_JOYSTICKS);
		memset(joyPress, 0, NUM_OF_JOY_BTNS * NUM_OF_JOYSTICKS);
		memset(joyAxes, 0, NUM_OF_JOY_AXES * NUM_OF_JOYSTICKS);

		activeJoysticks = 0;

		for (unsigned i = 0; i < NUM_OF_JOYSTICKS; ++i)
			if (glfwJoystickPresent(i) == GL_TRUE) activeJoysticks++;

		mouseX = mouseY = 0;

		return isInit = Window::instance().isInitialized();
	}

	bool Input::step()
	{
		INIT_ASSERT(Input);

		int count;

		for (unsigned i = 0; i < NUM_OF_KEYS; ++i)
		{
			keyState[i] = keyPress[i] > keyRelease[i];

			if (glfwGetKey(Window::instance().window, i) == GLFW_PRESS) keyPress[i]   = glfwGetTime();
			else														keyRelease[i] = glfwGetTime();
		}

		for (unsigned i = 0; i < NUM_OF_MOUSE_BTNS; ++i)
		{
			mouseState[i] = mousePress[i] > mouseRelease[i];

			if (glfwGetMouseButton(Window::instance().window, i) == GLFW_PRESS) mousePress[i]   = glfwGetTime();
			else																mouseRelease[i] = glfwGetTime();
		}

		for (unsigned i = 0; i < activeJoysticks; ++i)
		{
			for (unsigned j = 0; j < NUM_OF_JOY_BTNS; ++j)
			{
				joyState[i][j] = joyPress[i][j] > joyRelease[i][j];

				if (glfwGetJoystickButtons(i, &count)[j] == GLFW_PRESS) joyPress[i][j] = glfwGetTime();
				else													joyRelease[i][j] = glfwGetTime();
			}
		}

		double x, y;
		glfwGetCursorPos(Window::instance().window, &x, &y);

		mouseX = x;
		mouseY = y;

		for (unsigned i = 0; i < activeJoysticks; ++i)
			for (unsigned j = 0; j < NUM_OF_JOY_AXES; ++j)
				joyAxes[i][j] = glfwGetJoystickAxes(i, &count)[j];

		return false;
	}

	bool Input::getKey(unsigned key) { INIT_ASSERT(Input); return keyPress[key] > keyRelease[key]; }
	bool Input::getKeyPress(unsigned key) { INIT_ASSERT(Input); return getKey(key) && !keyState[key]; }
	bool Input::getKeyRelease(unsigned key) { INIT_ASSERT(Input); return !getKey(key) && keyState[key]; }

	float Input::keyDelta(unsigned key) { INIT_ASSERT(Input); return keyPress[key] - keyRelease[key]; }

	bool Input::getMouseButton(unsigned key) { INIT_ASSERT(Input); return mousePress[key] > mouseRelease[key]; }
	bool Input::getMouseButtonPress(unsigned key) { INIT_ASSERT(Input); return getMouseButton(key) && !mouseState[key]; }
	bool Input::getMouseButtonRelease(unsigned key) { INIT_ASSERT(Input); return !getMouseButton(key) && mouseState[key]; }

	int Input::getActiveJoysticks() { INIT_ASSERT(Input); return activeJoysticks; }

	float Input::getJoyAxis(int joy, unsigned axis) { INIT_ASSERT(Input); return joyAxes[joy][axis]; }
	bool Input::getJoy(int joy, unsigned key) { INIT_ASSERT(Input); return joyPress[joy][key] > joyRelease[joy][key]; }
	bool Input::getJoyPress(int joy, unsigned key) { INIT_ASSERT(Input); return getJoy(joy, key) && !joyState[joy][key]; }
	bool Input::getJoyRelease(int joy, unsigned key) { INIT_ASSERT(Input); return !getJoy(joy, key) && joyState[joy][key]; }

	float Input::getMouseX() { INIT_ASSERT(Input); return mouseX; }
	float Input::getMouseY() { INIT_ASSERT(Input); return mouseY; }
}