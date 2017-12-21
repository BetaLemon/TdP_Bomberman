#include "Player.h"

Player::Player() {};
Player::Player(int _id, Vector2 _pos) {
	id = _id;
	position = _pos;

	switch (id) {
	case 0:
		Renderer::Instance()->LoadTexture(PLAYER1_SPRITE, PATH_IMG + "player1.png");
		break;
	case 1:
		Renderer::Instance()->LoadTexture(PLAYER2_SPRITE, PATH_IMG + "player2.png");
		break;
	}
}

Player::~Player() {

}

void Player::Draw() {
	Vector2 spriteSize;
	switch (id) {
	case 0:
		//Renderer::Instance()->Clear();
		spriteSize = Renderer::Instance()->GetTextureSize(PLAYER1_SPRITE);
		spriteSize.x /= 3;
		spriteSize.y /= 4;
		Renderer::Instance()->PushSprite(PLAYER1_SPRITE, { 0,0,spriteSize.x,spriteSize.y }, { position.x, position.y, PLAYER_WIDTH, PLAYER_HEIGHT });
		//Renderer::Instance()->Render();
		break;
	case 1:
		//Renderer::Instance()->Clear();
		spriteSize = Renderer::Instance()->GetTextureSize(PLAYER2_SPRITE);
		spriteSize.x /= 3;
		spriteSize.y /= 4;
		Renderer::Instance()->PushSprite(PLAYER2_SPRITE, { 0,0,spriteSize.x,spriteSize.y }, { position.x, position.y, PLAYER_WIDTH, PLAYER_HEIGHT });
		//Renderer::Instance()->Render();
		break;
	}
	
}

//Cambiar el state del player segun un input recibido
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
			position = Vector2(position.x, position.y - 1 * velocity);
			state = NONE;
			break;
		case DOWN:
			position = Vector2(position.x, position.y + 1 * velocity);
			state = NONE;
			break;
		case LEFT:
			position = Vector2(position.x - 1*velocity, position.y);
			state = NONE;
			break;
		case RIGHT:
			position = Vector2(position.x + 1*velocity, position.y);
			state = NONE;
			break;
			
	}
	//Comprobar objetos

}