#include "PacMan.h"
#include "PacManGame.h"
#include <string>


void PacMan::make_move()
{

	if (this->selected_direction != NONE)
		this->change_direction(this->selected_direction);

	std::pair<int, int> new_location = this->getNewLocation(this->direction);

	char stuff_in_front = this->instance->get_pixel(new_location);
	switch (stuff_in_front)
	{
	case char(254):
		for (Ghost* ghost : this->instance->ghosts)
		{
			ghost->scare();
		}

	case char(250):
		this->add_score();

	case char(32):
		this->move(new_location);
		break;

	case char(1):
		for (Ghost* ghost : this->instance->ghosts)
		{
			if (ghost->getActorLocation() == new_location && ghost->isScared()) 
			{
				ghost->reset({12, 14}, UP);
			}
		}
		this->move(new_location);
		this->add_score();

		break;

	default:
		break;
	}

}

void PacMan::move(std::pair<int, int> &loc)
{
	this->instance->set_pixel(this->location, char(32));
	this->location = loc;
	this->instance->set_pixel(this->location, char(2), 6);
}

void PacMan::add_score()
{
	this->score++;
	this->instance->textview->setScore(this->score);
	if (this->score >= this->instance->final_score)
	{
		this->instance->loadNextLevel();
		if (this->instance->areLevelsEnded())
			this->instance->exitGame("YOU WIN. Score: " + std::to_string(this->score));
	}
}

void PacMan::remove_life()
{
	this->lifes--;
	this->instance->textview->setLives(this->lifes);
	if (this->lifes == 0)
		this->instance->exitGame("GAME OVER. Score: " + std::to_string(this->score));
}
