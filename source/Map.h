#ifndef MAP_H
#define MAP_H

#include <vector>
#include <map>
#include <string>

class PacManGame;

class Map
{
private:
	PacManGame* instance;
	

public:
	Map(PacManGame* instance);
	void reset();
	unsigned getFoodOnMap(std::vector<std::vector<int>> &map);
	static std::map<std::string, char> getPixNames();
	static char const getPixelByName(std::string name);

	static bool canWalkThrough(char ch);

	static unsigned getSizeX() { return 28; }
	static unsigned getSizeY() { return 31; }
};

#endif // MAP_H