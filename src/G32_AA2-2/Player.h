#pragma once
#include <vector>
#include "Types.h"

enum PlayerState{UP,DOWN,LEFT,RIGHT,BOMB,NONE};
//Struct used to store the position of the player
struct Point { 
	int x; int y; 
	Point(int valueX = 0, int valueY = 0) : x{ valueX }, y{ valueY }{}	
};

class Player {
private:
	int id; // 0 = player1, 1 = player2
	int points;
	int life;
	PlayerState state = NONE;
	Point position;
	//position
	//powerUp
	//sprite
public:
	Player();
	Player(int id,Point pos);
	~Player();
	void setPlayerState(SDL_Event e);
	void setPlayerStateToNONE() { state = NONE; }
	PlayerState getPlayerState() { return state; }
	Point getPosition() { return position; }

	//setPowerUp();
	//void setLife(int lf); getLife
	//setPoints, getPoints
	void Update();
	void Draw();
};