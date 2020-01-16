#pragma once

#include "Map.h"
#include "PacManGame.h"
#include "Util.h"

Map::Map(PacManGame* game) : instance(game)
{
}

void Map::reset()
{
	auto result = parse_csv("map.csv");
	this->instance->final_score = this->getFoodOnMap(result);
	for (int i = 0; i < result.size(); ++i)
	{
		auto line = result[i];
		for (int j = 0; j < line.size(); j++)
		{
			this->instance->set_pixel({ j, i }, line[j]);
		}
	}
}

unsigned Map::getFoodOnMap(std::vector<std::vector<int>> &map)
{
	int avaliable_score = 0;
	for (auto& vec : map)
	{
		for (int& ch : vec)
		{
			if (ch == 250)
			avaliable_score++;
		}
	}
	return avaliable_score;
}

bool Map::canWalkThrough(char ch)
{
	return ch == char(2) || ch == char(32) || ch == char(254) || ch == char(250);
}