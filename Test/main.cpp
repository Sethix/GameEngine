#include "Window.h"
#include "Input.h"

using namespace JTL;

int main()
{
	auto &window = Window::instance();
	window.init(400, 400);

	auto &input = Input::instance();
	input.init();

	while (window.step())
	{
		input.step();
		
		if (input.getJoy(0, 0) || input.getKey(32))
			window.Exit();

	}

	window.term();
	input.term();

	return 0;
}