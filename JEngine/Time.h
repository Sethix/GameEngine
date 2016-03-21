// TODO : Documentation and clean-up

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

		float getTotalTime();
		float getDeltaTime();

		bool init() { return isInit = Window::instance().isInitialized(); }
		bool step();
		void term() { INIT_ASSERT(Time); }

		bool isInitialized() { return isInit; }
	};

}