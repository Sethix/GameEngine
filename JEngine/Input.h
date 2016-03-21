// TODO : Documentation and clean-up

#pragma once
#include "Window.h"

#define NUM_OF_KEYS 400
#define NUM_OF_MOUSE_BTNS 16
#define NUM_OF_JOYSTICKS 16
#define NUM_OF_JOY_AXES 16
#define NUM_OF_JOY_BTNS 64

namespace JTL
{

	class Input
	{
		bool isInit;
		float keyRelease[NUM_OF_KEYS];
		float keyPress[NUM_OF_KEYS];
		bool keyState[NUM_OF_KEYS];

		float mouseRelease[NUM_OF_MOUSE_BTNS];
		float mousePress[NUM_OF_MOUSE_BTNS];
		bool mouseState[NUM_OF_MOUSE_BTNS];

		int activeJoysticks;
		float joyAxes[NUM_OF_JOYSTICKS][NUM_OF_JOY_AXES];

		float joyRelease[NUM_OF_JOYSTICKS][NUM_OF_JOY_BTNS];
		float joyPress[NUM_OF_JOYSTICKS][NUM_OF_JOY_BTNS];
		bool joyState[NUM_OF_JOYSTICKS][NUM_OF_JOY_BTNS];

		Input::Input() : isInit(false) {}

		float mouseX, mouseY;

		friend class Window;

	public:
		static Input &instance() { static Input instance; return instance; }

		bool init();
		bool step();
		void term() {}

		bool getKey(unsigned);
		bool getKeyPress(unsigned);
		bool getKeyRelease(unsigned);

		bool getMouseButton(unsigned);
		bool getMouseButtonPress(unsigned);
		bool getMouseButtonRelease(unsigned);

		int getActiveJoysticks();
		
		float getJoyAxis(int, unsigned);
		bool getJoy(int, unsigned);
		bool getJoyPress(int, unsigned);
		bool getJoyRelease(int, unsigned);

		float keyDelta(unsigned);

		float getMouseX();
		float getMouseY();

		bool isInitialized() { return isInit; }
	};

}