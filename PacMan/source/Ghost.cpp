#include "Ghost.h"
#include "PacManGame.h"
#include "Map"

E_Direction Ghost::getOppositeDirection(E_Direction direction)
{
	switch (direction)
	{
	case UP:
		return DOWN;
	case DOWN:
		return UP;
	case LEFT:
		return RIGHT;
	case RIGHT:
		return LEFT;
	default:
		return NONE;
	}
}

std::vector<E_Direction> Ghost::getAvailableDirections()
{
	std::pair<std::pair<int, int>, E_Direction> directions[4];
	directions[0] = { { this->location.first, this->location.second - 1 }, UP };
	directions[1] = { { this->location.first, this->location.second + 1 }, DOWN };
	directions[2] = { { this->location.first + 1, this->location.second }, RIGHT };
	directions[3] = { { this->location.first - 1, this->location.second }, LEFT };

	std::vector<E_Direction> res;

	for (auto direction : directions)
	{
		char in_direction = this->instance->get_pixel(direction.first);
		if (Map::canWalkThrough(in_direction))
			res.push_back(direction.second);
	}
	return res;
}

void Ghost::reset(std::pair<int, int> location, E_Direction direction)
{
	if (this->location.first != -1)
	{
		this->instance->set_pixel(this->location, this->stepped_on);
	}
	this->stepped_on = char(32);
	this->location = location;
	this->direction = direction;
	this->instance->set_pixel(this->location, this->skin);
}

bool Ghost::isInIntersection()
{
	std::pair<int, int> new_location = this->getNewLocation(this->direction);
	char in_front = this->instance->get_pixel(this->getNewLocation(this->direction));
	return this->getAvailableDirections().size() > 2 || !Map::canWalkThrough(in_front);
}

E_Direction Ghost::calcBestDirection()
{
	std::vector<E_Direction> available_directions = this->getAvailableDirections();
	std::pair<E_Direction, int> best_variant = {NONE, 100000000000};
	for (E_Direction direction : available_directions)
	{
		auto ghost_location = this->getNewLocation(direction);
		auto pacman_location = this->instance->pacman->getActorLocation();
		// Using manhattan metrics
		int distance = abs(ghost_location.first - pacman_location.first) + abs(ghost_location.second - pacman_location.second);
		if (distance < best_variant.second) 
			best_variant = { direction, distance };
	}
	return best_variant.first;
}

E_Direction Ghost::calcWorstDirection()
{
	std::vector<E_Direction> available_directions = this->getAvailableDirections();
	std::pair<E_Direction, int> best_variant = { NONE, -100000000000 };
	for (E_Direction direction : available_directions)
	{
		auto ghost_location = this->getNewLocation(direction);
		auto pacman_location = this->instance->pacman->getActorLocation();
		// Using manhattan metrics
		int distance = abs(ghost_location.first - pacman_location.first) + abs(ghost_location.second - pacman_location.second);
		if (distance > best_variant.second)
			best_variant = { direction, distance };
	}
	return best_variant.first;
}

bool Ghost::isNear(int length)
{
	auto ghost_location = this->getActorLocation();
	auto pacman_location = this->instance->pacman->getActorLocation();

	return (abs(ghost_location.first - pacman_location.first) + abs(ghost_location.second - pacman_location.second)) <= length;
}

void Ghost::scare()
{
	this->change_direction(this->calcWorstDirection());
	this->scared_time = std::chrono::system_clock::now();
}

bool Ghost::isScared()
{
	return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - this->scared_time).count() < 5;
}

void Ghost::rotateRandomly()
{
	std::vector<E_Direction> directions = this->getAvailableDirections();
	auto backwards_it = std::find(directions.begin(), directions.end(), Ghost::getOppositeDirection(this->direction));
	if (directions.size() != 1 && backwards_it != directions.end())
		directions.erase(backwards_it);
	E_Direction direction = directions[rand() % directions.size()];
	this->change_direction(direction);
}

void Ghost::make_move()
{
	std::pair<int, int> new_location = this->getNewLocation(this->direction);
	char stuff_in_front = this->instance->get_pixel(new_location);

	if (this->isNear(1) && !this->isScared())
	{
		this->instance->pacman->remove_life();
		this->instance->reset_actors();
	}

	if (this->isScared() && this->isNear())
	{
		this->change_direction(this->calcWorstDirection());
	}

	else if (this->isInIntersection()) {
		if (this->isNear())
		{
			this->change_direction(this->calcBestDirection());
		}
		else 
		{
			this->rotateRandomly();
		}
	}

	new_location = this->getNewLocation(this->direction);
	stuff_in_front = this->instance->get_pixel(new_location);
	switch (stuff_in_front)
	{
		case char(250):
		case char(254):
		case char(32):
		case char(1):
			this->instance->set_pixel(this->location, this->stepped_on);
			this->stepped_on = stuff_in_front;
			this->location = new_location;
			this->instance->set_pixel(this->location, char(1), this->isScared() ? 9 : this->color);
		default:
			break;
	}

}
