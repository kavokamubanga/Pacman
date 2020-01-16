#pragma once
#include <vector>

class PacManGame;

class Map
{
private:
	PacManGame* instance;
public:
	Map(PacManGame* instance);
	void reset();
	unsigned getFoodOnMap(std::vector<std::vector<int>> &map);

	static bool canWalkThrough(char ch);

	static unsigned getSizeX() { return 28; }
	static unsigned getSizeY() { return 31; }
};