#include "Actor.h"
#include "PacManGame.h"

Actor::Actor(PacManGame* instance, char skin = char(1)) : instance(instance), skin(skin) {}

void Actor::reset(std::pair<int, int> location, E_Direction direction)
{
	if (this->location.first != -1)
	{
		this->instance->set_pixel(this->location, char(32));
	}
	this->location = location;
	this->direction = direction;
	this->instance->set_pixel(this->location, this->skin);
}

void Actor::change_direction(E_Direction direction)
{
	char stuff_in_front_after_change = this->instance->get_pixel(this->getNewLocation(direction));

	if (Map::canWalkThrough(stuff_in_front_after_change))
	{
		this->direction = direction;
		this->selected_direction = NONE;
	}
	else
	{
		this->selected_direction = direction;
	}
}

std::pair<int, int> Actor::getNewLocation(E_Direction direction)
{
	std::pair<int, int> new_location;
	switch (direction)
	{
	case UP:
		new_location = { this->location.first, this->location.second - 1 };
		break;
	case DOWN:
		new_location = { this->location.first, this->location.second + 1 };
		break;
	case LEFT:
		new_location = { this->location.first - 1, this->location.second };
		break;
	case RIGHT:
		new_location = { this->location.first + 1, this->location.second };
		break;
	};
	return new_location;
}

void Actor::tick(int ms_passed) 
{
	this->time_passed += ms_passed;
	if (this->time_passed >= this->getSpeed())
	{
		this->make_move();
		this->time_passed = 0;
	}
}