// TODO : Documentation and clean-up

#pragma once
#include <cassert>
#include <typeinfo>

#define INIT_ASSERT(name) assert(isInit && #name "not initialized!")

struct GLFWwindow;

namespace JTL
{

	class Window
	{
		bool isInit, exit;
		int width, height;
		Window() : isInit(false), exit(false) {}

		GLFWwindow *window;

		friend class Input;

	public:

		static Window &instance() { static Window instance; return instance; }
		bool init(int Width = 800, int Height = 600, const char* Title = "JTL::TEST.EXE", 
				  bool resizeable = false, bool fullscreen = false);
		bool step();
		void term();

		void Exit() { exit = true; }

		int getWidth() { INIT_ASSERT(Window); return width; }
		int getHeight() { INIT_ASSERT(Window); return height; }
		bool	 isInitialized() { return isInit; }
	};

}