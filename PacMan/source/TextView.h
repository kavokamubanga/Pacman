#pragma once

class PacManGame;

class TextView
{
private:
	PacManGame* instance;

public:
	TextView(PacManGame* instance);
	void draw_border();
	void setScore(int score);
	void setLives(int life);
};