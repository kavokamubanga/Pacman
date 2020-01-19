#include "Basegame.h"
#include <conio.h>
#include <Windows.h>
#include <chrono>

BaseGame::BaseGame(int w, int h) : height(h), width(w)
{

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.nFont = 0;
	cfi.dwFontSize.X = 12;
	cfi.dwFontSize.Y = 16;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;

	wcscpy_s(cfi.FaceName, L"Terminal");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	SMALL_RECT windowSize = { 0, 0, short(w + 1), short(h + 1) };
	COORD windowBufSize = { short(w + 2), short(h + 2) };

	HANDLE mConsole;
	HANDLE mConsoleIn;

	CHAR_INFO* mChiBuffer;
	COORD mDwBufferSize;
	COORD mDwBufferCoord;
	SMALL_RECT mLpWriteRegion;

	mConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	mConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleScreenBufferSize(mConsole, windowBufSize);
	SetConsoleWindowInfo(mConsole, TRUE, &windowSize);

	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(mConsole, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(mConsole, &cursorInfo);

	mChiBuffer = (CHAR_INFO*)malloc((w + 2) * (h + 2) * sizeof(CHAR_INFO));

	mDwBufferSize.X = w + 2;
	mDwBufferSize.Y = h + 2;

	mDwBufferCoord.X = 0;
	mDwBufferCoord.Y = 0;

	mLpWriteRegion.Left = 0;
	mLpWriteRegion.Top = 0;
	mLpWriteRegion.Right = w + 2;
	mLpWriteRegion.Bottom = h + 2;


	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), {short(w + 2), short(h + 2)});

	this->screen = new char* [h];
	for (int h = 0; h < this->height; ++h)
	{
		this->screen[h] = new char[w];
		for (int w = 0;w < this->width;++w)
		{
			this->screen[h][w] = ' ';
		}
	}
}
BaseGame::~BaseGame()
{
	for (int h = 0; h < this->height; ++h)
	{
		delete[] this->screen[h];
	}
	delete[] this->screen;
	
}

void BaseGame::set_pixel(std::pair<int, int> coord, char symb, int color)
{
	this->screen[coord.second][coord.first] = symb;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { short(this->left_margin + coord.first), short(this->top_margin + coord.second) });
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	std::cout << symb;
}

char BaseGame::get_pixel(std::pair<int, int> coord)
{
	return this->screen[coord.second][coord.first];
}
void BaseGame::exitGame(std::string msg)
{
	this->exit_message = msg;
	this->exit = true;
}

void BaseGame::start()
{
	this->on_begin();

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();

	while (!this->exit)
	{
		end = std::chrono::system_clock::now();
		this->on_tick(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
		start = end;
		if (_kbhit())
		{
			this->on_key_pressed(_getch());
		}
	}

	for (int h = 0; h < this->height; ++h)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { short(this->left_margin), short(this->top_margin + h) });
		for (int w = 0; w < this->width; ++w)
		{
			std::cout << ' ';
		}
	}
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { short(this->left_margin), short(this->top_margin + this->height / 2) });
	std::cout << this->exit_message;
	std::cout << "\a";
	Sleep(3000);
	_getch();
}