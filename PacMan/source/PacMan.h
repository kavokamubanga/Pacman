#pragma once
#include <deque>
#include "Actor.h"

class PacMan : public Actor
{
private:
	int score = 1;
	int lifes = 3;
	void move(std::pair<int, int> &loc);
public:
	void make_move() override;
	PacMan(PacManGame* instance) : Actor(instance, char(2)) {}
	void remove_life();
	void add_score();
	virtual int getSpeed() override { return 200000; }
};
