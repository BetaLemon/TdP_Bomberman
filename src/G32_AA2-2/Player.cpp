#include "Player.h"

Player::Player() {};
Player::Player(int _id, Point _pos) {
	id = _id;
	position = _pos;
}

//Cambiar el state del player segun un imput recivido
void Player::setPlayerState(SDL_Event e) {
	
	//controles jugador1
	if (id == 0) {
		switch (e.key.keysym.sym) {
			case SDLK_w:
				state = UP;
				break;
			case SDLK_s:
				state = DOWN;
				break;
			case SDLK_a:
				state = LEFT;
				break;
			case SDLK_d:
				state = RIGHT;
				break;
			//case bomb
		}
	}
	//controles jugador2
	else if (id == 1) {
		switch (e.key.keysym.sym) {
		case SDLK_i:
			state = UP;
			break;
		case SDLK_k:
			state = DOWN;
			break;
		case SDLK_j:
			state = LEFT;
			break;
		case SDLK_l:
			state = RIGHT;
			break;
		}
	}
}

void Player::Update() {
	//Mover el Personaje e instanciar las bombas
	switch (state) {
		case UP:
			position =  Point(position.x, position.y - 1);
			state = NONE;
			break;
		case DOWN:
			position = Point(position.x, position.y + 1);
			state = NONE;
			break;
		case LEFT:
			position = Point(position.x - 1, position.y);
			state = NONE;
			break;
		case RIGHT:
			position = Point(position.x + 1, position.y);
			state = NONE;
			break;
		case BOMB:
			//Create a bomb;
	}
	//Comprobar objetos

}