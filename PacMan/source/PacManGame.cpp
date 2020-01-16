#include "PacManGame.h"
#include <Windows.h>

PacManGame::PacManGame() : BaseGame(
		Map::getSizeX(),
		Map::getSizeY() + 5
	)
{
	this->map = new Map(this);
	this->pacman = new PacMan(this);
	this->textview = new TextView(this);
	int colors[4] = { 10, 11, 12, 13 };
	for(int i = 0; i < 4; ++i)
		this->ghosts[i] = new Ghost(this, colors[i]);
}

PacManGame::~PacManGame()
{
	delete this->map;
	delete this->pacman;
	delete this->textview;
	for (int i = 0; i < 4; ++i)
		delete this->ghosts[i];
}

void PacManGame::on_begin()
{
	this->loadNextLevel();
	this->textview->draw_border();
	this->textview->setScore(0);
	this->textview->setLives(3);
}

void PacManGame::reset_actors()
{
	this->pacman->reset({ 1, 11 }, RIGHT);

	for (int i = 0; i < 4; ++i)
		this->ghosts[i]->reset({ 12 + i,14 }, UP);
}

void PacManGame::loadNextLevel()
{
	this->level++;
	this->map->reset();
	this->reset_actors();
}
	
void PacManGame::on_tick(int ms_passed)
{
	this->pacman->tick(ms_passed);
	for(int i = 0;i < 4;i++)
		this->ghosts[i]->tick(ms_passed);
}

void PacManGame::on_key_pressed(char key)
{
	switch (key)
	{
	case 'W':
	case 'w':
		this->pacman->change_direction(UP);
		break;
	case 'S':
	case 's':
		this->pacman->change_direction(DOWN);
		break;
	case 'A':
	case 'a':
		this->pacman->change_direction(LEFT);
		break;
	case 'D':
	case 'd':
		this->pacman->change_direction(RIGHT);
		break;
	}
}