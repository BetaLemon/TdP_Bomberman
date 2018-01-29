#include "Player.h"
#include <iostream>

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

	points = 0;
	life = 3;
	canMove = { false, false, false, false };
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
		Renderer::Instance()->PushSprite(PLAYER1_SPRITE, { spriteSize.x*(spriteX/5),spriteSize.y*spriteY,spriteSize.x,spriteSize.y},
			{ position.x - (PLAYER_WIDTH/2), position.y - (PLAYER_HEIGHT/2), PLAYER_WIDTH, PLAYER_HEIGHT });
		//Renderer::Instance()->Render();
		
		break;
	case 1:
		//Renderer::Instance()->Clear();
		spriteSize = Renderer::Instance()->GetTextureSize(PLAYER2_SPRITE);
		spriteSize.x /= 3;
		spriteSize.y /= 4;
		Renderer::Instance()->PushSprite(PLAYER2_SPRITE, { spriteSize.x*(spriteX/5),spriteSize.y*spriteY,spriteSize.x,spriteSize.y },
			{ position.x - (PLAYER_WIDTH/2), position.y - (PLAYER_HEIGHT/2), PLAYER_WIDTH, PLAYER_HEIGHT });
		//Renderer::Instance()->Render();

		break;
	}
	bomb.Bomb::Draw();
}

//Cambiar el state del player segun un input recibido
void Player::setPlayerState(SDL_Event e,const Uint8 *array) {
	
	//state = _state;
	if (id == 0) {

		if (array[SDL_SCANCODE_W]) {
			state = UP;
			facing = UP;
		}
		if (array[SDL_SCANCODE_S]) {
			state = DOWN;
			facing = DOWN;
		}
		if (array[SDL_SCANCODE_A]) {
			state = LEFT;
			facing = LEFT;
		}
		if (array[SDL_SCANCODE_D]) {
			state = RIGHT;
			facing = RIGHT;
		}
		if (array[SDL_SCANCODE_SPACE]) {
			state = BOMB;

		}
	}
	//controles jugador2
	
	 else if (id == 1) {

		if (array[SDL_SCANCODE_UP]) {
			state = UP;
			facing = UP;
		}
		if (array[SDL_SCANCODE_DOWN]) {
			state = DOWN;
			facing = DOWN;
		}
		if (array[SDL_SCANCODE_LEFT]) {
			state = LEFT;
			facing = LEFT;
		}
		if (array[SDL_SCANCODE_RIGHT]) {
			state = RIGHT;
			facing = RIGHT;
		}
		if (array[SDL_SCANCODE_RCTRL]) {

			state = BOMB;
		}
	}
}

Vector2 Player::getGridPos() {
	Vector2 tmp;
	tmp.x = floor(position.x / CELL_WIDTH);
	tmp.y = floor((position.y - HUD_HEIGHT) / CELL_HEIGHT);
	return tmp;
}

void Player::Update() {
	//Mover el Personaje e instanciar las bombas
	switch (state) {
		case UP:
			if (canMove.up) {
				position = Vector2(position.x, position.y - CELL_HEIGHT);
			}
			spriteY = 0;
			//Hasta 10 para que se reduzca la velocidad
			if (spriteX == 10) {
				spriteX = 0;
			}
			else spriteX++;
			state = NONE;
			break;
		case DOWN:
			if (canMove.down) {
				position = Vector2(position.x, position.y + CELL_HEIGHT);
			}
			spriteY = 2;
			if (spriteX == 10) {
				spriteX = 0;
			}
			else spriteX++;
			state = NONE;
			break;
		case LEFT:
			if (canMove.left) {
				position = Vector2(position.x - CELL_WIDTH, position.y);
			}
			spriteY = 1;
			if (spriteX == 10) {
				spriteX = 0;
			}
			else spriteX++;
			state = NONE;
			break;
		case RIGHT:
			if (canMove.right) {
				position = Vector2(position.x + CELL_WIDTH, position.y);
			}
			spriteY = 3;
			if (spriteX == 10) {
				spriteX = 0;
			}
			else spriteX++;
			state = NONE;
			break;
		case BOMB:
			if (bomb.getState() == BombState::WAITING) {
				bomb.Init(position);
			}
			state = NONE;
			break;
	}
	bomb.Update();
	//std::cout << "Bomb State: " << bomb.getState() << std::endl;
}

int Player::getPoints() {
	return points;
}
void Player::addPoints(int amount) {
	points = points + amount;
}

int Player::getLife() { return life; }

void Player::setCanMove(PlayerMoveAllow cM) {
	canMove = cM;
}


