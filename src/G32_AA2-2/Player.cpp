#include "Player.h"

Player::Player() {};
Player::Player(int _id, Point _pos) {
	id = _id;
	position = _pos;
}

Player::~Player() {

}

//Cambiar el state del player segun un imput recivido
void Player::setPlayerState(SDL_Event e) {
	
	//controles jugador1
	if (id == 0) {
		switch (e.key.keysym.sym) {
			case SDLK_w:
				state = UP;
				facing = UP;
				break;
			case SDLK_s:
				state = DOWN;
				facing = DOWN;
				break;
			case SDLK_a:
				state = LEFT;
				facing = LEFT;
				break;
			case SDLK_d:
				state = RIGHT;
				facing = RIGHT;
				break;
			case SDLK_SPACE:
				state = BOMB;
				break;
		}
	}
	//controles jugador2
	else if (id == 1) {
		switch (e.key.keysym.sym) {
		case SDLK_UP:
			state = UP;
			facing = UP;
			break;
		case SDLK_DOWN:
			state = DOWN;
			facing = DOWN;
			break;
		case SDLK_LEFT:
			state = LEFT;
			facing = LEFT;
			break;
		case SDLK_RIGHT:
			state = RIGHT;
			facing = RIGHT;
			break;
		case SDLK_RCTRL:
			state = BOMB;
			break;
		}
	}
}



void Player::Update() {
	//Mover el Personaje e instanciar las bombas
	switch (state) {
		case UP:
			position =  Point(position.x, position.y - 1 * velocity);
			state = NONE;
			break;
		case DOWN:
			position = Point(position.x, position.y + 1 * velocity);
			state = NONE;
			break;
		case LEFT:
			position = Point(position.x - 1*velocity, position.y);
			state = NONE;
			break;
		case RIGHT:
			position = Point(position.x + 1*velocity, position.y);
			state = NONE;
			break;
			
	}
	//Comprobar objetos

}