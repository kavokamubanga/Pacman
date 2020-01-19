#ifndef GHOST_H
#define GHOST_H

#include "Actor.h"
#include <vector>
#include <chrono>

class Ghost : public Actor
{
private:
	char stepped_on = char(32);
	int color;
	std::chrono::time_point<std::chrono::system_clock> scared_time = std::chrono::system_clock::now() - std::chrono::hours(24);

	std::vector<E_Direction> getAvailableDirections();
	bool isInIntersection();
	static E_Direction getOppositeDirection(E_Direction direction);
	E_Direction calcBestDirection(); // Nearest to pacman
	E_Direction calcWorstDirection(); // Farest from pacman
	bool isNear(int length = 8);
	void rotateRandomly();
public:
	bool isScared();
	void scare();
	void make_move() override;
	void reset(std::pair<int, int> location, E_Direction direction) override;
	Ghost(PacManGame* instance, int color = 12) : Actor(instance, char(1)), color(color) { }
	virtual int getSpeed() override { return this->isScared() ? 400000 : 300000; }
};

#endif // GHOST_H