#pragma once
#include <vector>
#include <Windows.h>
#include "ConsoleScreen.h"
#include "Food.h"
enum Direction
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NONE
};
struct Snake
{
	int pos_x = 1;
	int pos_y = 1;
	constexpr static char sign = '-';
	Direction direction = RIGHT;


	bool eaten = false;
	Snake& operator=(const Snake& s)
	{
		pos_x = s.pos_x;
		pos_y = s.pos_y;
		direction = s.direction;
		return *this;
	}

	void update_direction()
	{
		//if (GetAsyncKeyState((unsigned short)'A') & 0x8000) // Left
		if (GetAsyncKeyState((unsigned short)37) & 0x8000) // Left Arrow Key
		{
			if (direction != RIGHT)
				direction = LEFT;
		}


		//if (GetAsyncKeyState((unsigned short)'D') & 0x8000) // Right
		if (GetAsyncKeyState((unsigned short)39) & 0x8000) // Right Arrow Key
		{
			if (direction != LEFT)
				direction = RIGHT;
		}


		//if (GetAsyncKeyState((unsigned short)'W') & 0x8000) // Up
		if (GetAsyncKeyState((unsigned short)38) & 0x8000) // Up Arrow Key
		{

			if (direction != DOWN)
				direction = UP;
		}


		//if (GetAsyncKeyState((unsigned short)'S') & 0x8000) // Down
		if (GetAsyncKeyState((unsigned short)40) & 0x8000) // Down Arrow Key
		{
			if (direction != UP)
				direction = DOWN;
		}

	}
	void update()
	{
		switch (direction)
		{
		case DOWN:
			if (pos_y < nScreenHeight - 2)
			{
				++pos_y;
			}
			else
			{
				pos_y = 1;
			}

			break;
		case UP:
			if (pos_y > 1)
			{
				--pos_y;

			}
			else
			{
				pos_y = nScreenHeight - 2;
			}

			break;
		case LEFT:
			if (pos_x > 1)
			{

				--pos_x;
			}
			else
			{
				pos_x = nScreenWidth - 2;
			}

			break;
		case RIGHT:
			if (pos_x < nScreenWidth - 2)
			{
				++pos_x;
			}
			else
			{
				pos_x = 1;
			}
			break;
		default:
			break;
		}

	}
	void eat(Food& food)
	{
		if (pos_x == food.pos_x && pos_y == food.pos_y)
		{
			eaten = food.eaten = true;

		}
	}

};
struct Head : Snake
{
	std::vector<Snake> tail;
	void set_on_map(ConsoleScreen& console_screen)
	{
		static std::size_t i = 0;
		static bool achived = false;
		if (i == 4 && !achived)
		{
			achived = true;
			i = 0;
			tail.push_back(*this);
			//console_screen.reset_map(pos_x, pos_y);
		}
		else
		{
			++i;
			tail.push_back(*this);
		}

		if (achived)
		{

			if (!eaten)
			{
				console_screen.reset_map(tail.front().pos_x, tail.front().pos_y);
				tail.erase(tail.begin());


			}
			else
			{
				eaten = false;
			}

		}
		update();
		console_screen.set_map(pos_x, pos_y, sign);

	}
	bool check_lose()
	{
		for (const auto& s : tail)
		{
			if (s.pos_x == pos_x && s.pos_y == pos_y)
			{
				return true;
			}
		}
		return false;
	}
	void control(const std::vector<Position>& path)
	{
		

		Position p = path.back();
		if (p.x > pos_x)
		{
			direction = RIGHT;
		}
		else if (p.x < pos_x)
		{
			direction = LEFT;
		}
		else if (p.y > pos_y)
		{
			direction = DOWN;
		}
		else if (p.y < pos_y)
		{
			direction = UP;
		}
		
	}

};