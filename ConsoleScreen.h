#pragma once
#include <memory>
#include <Windows.h>
const int nScreenWidth = 60;			// Console Screen Size X (columns)
const int nScreenHeight = 20;			// Console Screen Size Y (rows)
struct ConsoleScreen
{
	
	std::shared_ptr<wchar_t[]> screen = nullptr;
	static constexpr char wall = '0';
	static constexpr std::size_t numb_row = nScreenWidth;
	static constexpr std::size_t numb_column = nScreenHeight;
	DWORD dwBytesWritten = 0;
	HANDLE hConsole;

	ConsoleScreen() : screen(new wchar_t[numb_row * numb_column])
	{
		hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetConsoleActiveScreenBuffer(hConsole);

	}
	~ConsoleScreen()
	{

	}
	void init_map()
	{
		for (std::size_t row = 0; row < nScreenHeight; ++row)
		{
			for (size_t column = 0; column < nScreenWidth; ++column)
			{
				if (row == 0)
					screen[column] = wall;
				else if (row == (nScreenHeight - 1))
					screen[row * nScreenWidth + column] = wall;
				else
				{
					screen[row * nScreenWidth + column] = ' ';
				}
			}
			screen[row * nScreenWidth] = wall;
			screen[row * nScreenWidth + nScreenWidth - 1] = wall;
		}
	}
	void set_map(short posx, short posy, char c)
	{
		if (posx < nScreenWidth - 1 && posy < nScreenHeight - 1 && posx > 0 && posy > 0)
		{
			screen[posy * nScreenWidth + posx] = c;
		}

	}
	void reset_map(short posx, short posy)
	{
		if (posx < nScreenWidth - 1 && posy < nScreenHeight - 1 && posx > 0 && posy > 0)
		{
			screen[posy * nScreenWidth + posx] = ' ';
		}
	}
	wchar_t get_value(short posx, short posy) const
	{
		return screen[posy * nScreenWidth + posx];
	}
	void reset_all_map()
	{
		for (std::size_t i = 1; i < nScreenHeight - 1; i++)
		{

			for (std::size_t j = 1; j < nScreenWidth - 1; j++)
			{
				reset_map(i, j);
			}
		}
	}
	void draw()
	{
		WriteConsoleOutputCharacter(hConsole, screen.get(), nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);

	}
};