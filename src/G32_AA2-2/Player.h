#pragma once
#include <vector>
#include "Types.h"
#include "Types.h"
#include "Bomb.h"
#include "Renderer.h"

enum PlayerState{UP,DOWN,LEFT,RIGHT,BOMB,NONE};
//Struct used to store the position of the player

struct PlayerMoveAllow { bool up, down, left, right; };

class Player {
private:
	int id; // 0 = player1, 1 = player2
	int points;
	int life;
	int spriteX = 1;
	int spriteY = 1;
	PlayerState state = NONE;
	Vector2 position;
	Vector2 calculatePosition;
	int width, height;
	int velocity = 5;
	Bomb bomb = Bomb();
	PlayerState facing = LEFT;
	PlayerMoveAllow canMove;
	//powerUp
	//sprite
public:
	
	Player();
	Player(int id,Vector2 pos);
	~Player();
	void setPlayerState(SDL_Event e, const Uint8 *array);
	void setPlayerStateToNONE() { state = NONE; }
	PlayerState getPlayerState() { return state; }
	PlayerState getPlayerFacing() { return facing; }
	Vector2 getPosition() { return position; }
	SDL_Rect getCollider() {
		SDL_Rect coll = { position.x,position.y,width,height };
		return coll;
	}

	Vector2 getGridPos();
	int getPoints();
	void addPoints(int amount);
	int getLife();

	void setCanMove(PlayerMoveAllow cM);
	PlayerMoveAllow getCanMove() { return canMove; }

	Bomb getBomb() { return bomb; }
		
	//setPowerUp();

	void Update();
	void Draw();
};