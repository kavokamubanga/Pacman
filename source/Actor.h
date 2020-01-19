#ifndef ACTOR_H
#define ACTOR_H

#include <deque>

class PacManGame;

enum E_Direction { UP, DOWN, LEFT, RIGHT, NONE };

class Actor
{
protected:
	std::pair<int, int> location = { -1, -1 };
	E_Direction direction = NONE;
	E_Direction selected_direction = NONE;
	PacManGame* instance;
	std::pair<int, int> getNewLocation(E_Direction direction);
	char skin;
	int time_passed = 0;

public:
	Actor(PacManGame* instance, char skin);
	virtual int getSpeed() { return 300000; }
	virtual void reset(std::pair<int, int> location, E_Direction direction);
	virtual void make_move() = 0;
	virtual void tick(int ms_passed);
	std::pair<int, int> getActorLocation() const { return this->location; }
	void change_direction(E_Direction direction);
};

#endif // ACTOR_H