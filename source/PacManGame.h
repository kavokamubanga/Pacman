#ifndef PACMANGAME_H
#define PACMANGAME_h

#include "BaseGame.h"
#include "Map.h"
#include "PacMan.h"
#include "TextView.h"
#include "Ghost.h"

class PacManGame : public BaseGame
{
protected:
	void on_begin() override;
	void on_tick(int ms_passed) override;
	void on_key_pressed(char key) override;
	int level = 0;

public:
	int final_score;
	PacManGame();
	~PacManGame();

	void reset_actors();

	Map* map;
	PacMan* pacman;
	TextView* textview;
	Ghost* ghosts[4];
};

#endif // PACMANGAME_H