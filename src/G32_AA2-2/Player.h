#pragma once
#include <vector>
#include "Types.h"
#include "Types.h"
#include "Bomb.h"
#include "Renderer.h"

enum PlayerState{UP,DOWN,LEFT,RIGHT,BOMB,NONE};
//Struct used to store the position of the player


class Player {
private:
	int id; // 0 = player1, 1 = player2
	int points;
	int life;
	PlayerState state = NONE;
	Vector2 position;
	int width, height;
	int velocity = 5;
	Bomb bomb;
	PlayerState facing;
	//position
	//powerUp
	//sprite
public:
	
	Player();
	Player(int id,Vector2 pos);
	~Player();
	void setPlayerState(SDL_Event e);
	void setPlayerStateToNONE() { state = NONE; }
	PlayerState getPlayerState() { return state; }
	PlayerState getPlayerFacing() { return facing; }
	Vector2 getPosition() { return position; }
	SDL_Rect getCollider() {
		SDL_Rect coll = { position.x,position.y,width,height };
		return coll;
	}

	Bomb getBomb() { return bomb; }
		
	//setPowerUp();
	//void setLife(int lf); getLife
	//setPoints, getPoints
	void Update();
	void Draw();
};