#pragma once
#include "Window.h"

namespace JTL
{

	class Time
	{
		bool isInit;
		Time() : isInit(false) {}

		double previousTime;

	public:
		static Time &instance() { static Time instance; return instance; }

		bool init() { return isInit = Window::instance().isInitialized(); }
		bool step() { INIT_ASSERT(Time); return true; }
		void term() { INIT_ASSERT(Time); }

		bool isInitialized() { return isInit; }

		float getTotalTime();
		float getDeltaTime();
	};

}