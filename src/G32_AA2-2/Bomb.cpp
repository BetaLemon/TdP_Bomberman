#include "Bomb.h"
#include <iostream>

Bomb::Bomb() {
	timer = 0.0f;
	state = BombState::WAITING;
	Renderer::Instance()->LoadTexture(PLAY_BOMB_SPRITE, PATH_IMG + "items.png");
	bomb_s = Renderer::Instance()->GetTextureSize(PLAY_BOMB_SPRITE);
	bomb_s.x /= 3;
	bomb_s.y /= 2;

	Renderer::Instance()->LoadTexture(PLAY_EXPLOSION_SPRITE, PATH_IMG + "explosion.png");
	explos_s = Renderer::Instance()->GetTextureSize(PLAY_EXPLOSION_SPRITE);
	explos_s.x /= 4;
	explos_s.y /= 7;
}

void Bomb::Init(Vector2 _pos) {
	pos = _pos;
	timer = 0.0f;
	state = BombState::ACTIVE;
}

void Bomb::Update() {
	
	if (state == BombState::ACTIVE) {
		timer += 0.02f;
		explosionStage = -1;
		if (timer > 1.4f) { explosionStage = 0; }
		if (timer > 1.5f) { explosionStage = 1; }
		if (timer > 1.55f){ explosionStage = 2; }
		if (timer > 1.6f) { explosionStage = 3; exploded = true; }
		if (timer > 1.8f) {
			state = BombState::WAITING;
		}
	}
	else {
		exploded = false;
	}
}

void Bomb::setState(BombState _state) {
	state = _state;
}


void Bomb::Draw() {
	if (state == BombState::ACTIVE) {
		Renderer::Instance()->PushSprite(PLAY_BOMB_SPRITE, { bomb_s.x*0,bomb_s.y*1,bomb_s.x,bomb_s.y }, { pos.x - (PLAYER_WIDTH/2), pos.y - (PLAYER_HEIGHT/2), CELL_WIDTH, CELL_HEIGHT });
		
			// EXPLOSION:
		// Center:
		Renderer::Instance()->PushSprite(PLAY_EXPLOSION_SPRITE, { explos_s.x * explosionStage, explos_s.y * 0, explos_s.x,explos_s.y },
			{ pos.x - (PLAYER_WIDTH / 2), pos.y - (PLAYER_HEIGHT / 2), CELL_WIDTH, CELL_HEIGHT });
		// Up 1:
		Renderer::Instance()->PushSprite(PLAY_EXPLOSION_SPRITE, { explos_s.x * explosionStage, explos_s.y * 6 ,explos_s.x,explos_s.y },
			{ pos.x - (PLAYER_WIDTH / 2), pos.y - (PLAYER_HEIGHT / 2) - CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT });
		// Up 2:
		Renderer::Instance()->PushSprite(PLAY_EXPLOSION_SPRITE, { explos_s.x * explosionStage, explos_s.y * 3,explos_s.x,explos_s.y },
			{ pos.x - (PLAYER_WIDTH / 2), pos.y - (PLAYER_HEIGHT / 2) - (CELL_HEIGHT*2), CELL_WIDTH, CELL_HEIGHT });
		// Down 1:
		Renderer::Instance()->PushSprite(PLAY_EXPLOSION_SPRITE, { explos_s.x * explosionStage, explos_s.y * 6 ,explos_s.x,explos_s.y },
			{ pos.x - (PLAYER_WIDTH / 2), pos.y - (PLAYER_HEIGHT / 2) + CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT });
		// Down 2:
		Renderer::Instance()->PushSprite(PLAY_EXPLOSION_SPRITE, { explos_s.x * explosionStage, explos_s.y * 4 ,explos_s.x,explos_s.y },
			{ pos.x - (PLAYER_WIDTH / 2), pos.y - (PLAYER_HEIGHT / 2) + (CELL_HEIGHT * 2), CELL_WIDTH, CELL_HEIGHT });
		// Left 1:
		Renderer::Instance()->PushSprite(PLAY_EXPLOSION_SPRITE, { explos_s.x * explosionStage, explos_s.y * 5 ,explos_s.x,explos_s.y },
			{ pos.x - (PLAYER_WIDTH / 2) - CELL_WIDTH, pos.y - (PLAYER_HEIGHT / 2), CELL_WIDTH, CELL_HEIGHT });
		// Left 2:
		Renderer::Instance()->PushSprite(PLAY_EXPLOSION_SPRITE, { explos_s.x * explosionStage, explos_s.y * 1 ,explos_s.x,explos_s.y },
			{ pos.x - (PLAYER_WIDTH / 2) - (CELL_WIDTH*2), pos.y - (PLAYER_HEIGHT / 2), CELL_WIDTH, CELL_HEIGHT });
		// Right 1:
		Renderer::Instance()->PushSprite(PLAY_EXPLOSION_SPRITE, { explos_s.x * explosionStage, explos_s.y * 5 ,explos_s.x,explos_s.y },
			{ pos.x - (PLAYER_WIDTH / 2) + CELL_WIDTH, pos.y - (PLAYER_HEIGHT / 2), CELL_WIDTH, CELL_HEIGHT });
		// Right 2:
		Renderer::Instance()->PushSprite(PLAY_EXPLOSION_SPRITE, { explos_s.x * explosionStage, explos_s.y * 2  ,explos_s.x,explos_s.y },
			{ pos.x - (PLAYER_WIDTH / 2) + (CELL_WIDTH * 2), pos.y - (PLAYER_HEIGHT / 2), CELL_WIDTH, CELL_HEIGHT });
		

	}
	else {
		//Renderer::Instance()->PushSprite(PLAY_BOMB_SPRITE, { spriteSize.x * 0,spriteSize.y * 1,spriteSize.x,spriteSize.y }, { pos.x*CELL_WIDTH, pos.y*CELL_HEIGHT + HUD_HEIGHT, 0, 0 });
	}
}

Vector2 Bomb::getGridPos() {
	int x = floor(pos.x / CELL_WIDTH);
	int y = floor((pos.y - HUD_HEIGHT) / CELL_HEIGHT);
	return { x,y };
	std::cout << x << " " << y << std::endl;
}

bool Bomb::hasExploded() { return exploded; }