#pragma once

class Player {
private:
	int points;
	int life;
	//position
	//powerUp
	//sprite
public:
	Player();
	~Player();
	void setPlayerState(/**/);
	//getPlayerState();
	//setPowerUp();
	//void setLife(int lf); getLife
	//setPoints, getPoints
	void Update();
	void Draw();
};