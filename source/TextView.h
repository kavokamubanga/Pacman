#ifndef TEXTVIEW_H
#define TEXTVIEW_H

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

#endif // TEXTVIEW_H