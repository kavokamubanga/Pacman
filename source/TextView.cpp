#include "TextView.h"
#include "PacManGame.h"
#include "Map.h"
#include <string>

TextView::TextView(PacManGame* instance) : instance(instance) {}

void TextView::draw_border()
{
	
	for (int i = 0; i < Map::getSizeX(); ++i)
	{
		this->instance->set_pixel({ i, Map::getSizeY() + 2 }, char(196));
		this->instance->set_pixel({ i, Map::getSizeY() + 4 }, char(196));
	}

	
	this->instance->set_pixel({ 0, Map::getSizeY() + 2 }, char(218));
	this->instance->set_pixel({ 0, Map::getSizeY() + 3 }, char(179));
	this->instance->set_pixel({ 0, Map::getSizeY() + 4 }, char(192));

	
	this->instance->set_pixel({ Map::getSizeX() - 1, Map::getSizeY() + 2 }, char(191));
	this->instance->set_pixel({ Map::getSizeX() - 1, Map::getSizeY() + 3 }, char(179));
	this->instance->set_pixel({ Map::getSizeX() - 1, Map::getSizeY() + 4 }, char(217));

	this->instance->set_pixel({ Map::getSizeX() / 2, Map::getSizeY() + 2 }, char(194));
	this->instance->set_pixel({ Map::getSizeX() / 2, Map::getSizeY() + 3 }, char(179));
	this->instance->set_pixel({ Map::getSizeX() / 2, Map::getSizeY() + 4 }, char(193));
}

void TextView::setScore(int score)
{
	std::string score_string = "Score:" + std::to_string(score);
	for (int i = 0; i < score_string.size(); ++i)
	{
		this->instance->set_pixel({ 1 + i, Map::getSizeY() + 3 }, score_string[i]);
	}
	
}

void TextView::setLives(int life)
{

	std::string life_string = "Lives:";
	for (int i = 0; i < 3; ++i)
	{
		life_string += " ";
		life_string += i < life ? char(1) : ' ';
	}
	for (int i = 0; i < life_string.size(); ++i)
	{
		this->instance->set_pixel({ Map::getSizeX() / 2 + (1 + i), Map::getSizeY() + 3 }, life_string[i]);
	}
}
