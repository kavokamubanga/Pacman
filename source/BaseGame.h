#ifndef BASEGAME_H
#define BASEGAME_H

#include <deque>
#include <iostream>
#include <Windows.h>

class BaseGame
{
protected:
	char** screen;
	unsigned width, height;
	std::string exit_message;

	virtual void on_begin() = 0;
	virtual void on_key_pressed(char key) = 0;
	virtual void on_tick(int ms_passed) = 0;
private:
	int left_margin = 1, top_margin = 1;
public:
	BaseGame(int h, int w);
	virtual ~BaseGame();
	void start();
	void set_pixel(std::pair<int,int> coord, char symb, int color = 15);
	void exitGame(std::string);
	char get_pixel(std::pair<int,int> coord);
	bool exit;
};

#endif // BASEGAME_H