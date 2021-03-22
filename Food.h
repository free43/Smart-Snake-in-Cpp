#pragma once
#include "ConsoleScreen.h"
#include <chrono>
#include <random>
struct Food
{
	int pos_x;
	int pos_y;
	constexpr static char sign = '+';
	bool eaten = false;
	void set_on_map(ConsoleScreen& console_screen)
	{
		if (eaten)
		{
			console_screen.set_map(pos_x, pos_y, '-');
			eaten = false;
			do
			{
				spawn();

			} while (console_screen.get_value(pos_x, pos_y) != ' ');
			console_screen.set_map(pos_x, pos_y, sign);
		}
	}
	void spawn()
	{

		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::minstd_rand0 generator(seed);
		pos_x = (generator() % (nScreenWidth - 1));
		pos_x = pos_x == 0 ? 1 : pos_x;
		pos_y = (generator() % (nScreenHeight - 1));
		pos_y = pos_y == 0 ? 1 : pos_y;
	}
};
