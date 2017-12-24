#include "Bomb.h"
#include <iostream>

Bomb::Bomb() {
	timer = 0.0f;
	state = WAITING;
	Renderer::Instance()->LoadTexture(PLAY_CELL_SPRITE, PATH_IMG + "items.png");
}

void Bomb::Init(Vector2 _pos) {
	pos = _pos;
	timer = 0.0f;
	state = ACTIVE;
	
}

void Bomb::Update() {
	
	if (state == ACTIVE) {
		timer += 0.01f;
		if (timer > 1,5) {
			state = WAITING;
		}
	}
}

void Bomb::setState(BombState _state) {
	state = _state;
}


void Bomb::Draw() {
	
	Vector2 spriteSize = Renderer::Instance()->GetTextureSize(PLAY_CELL_SPRITE);
	spriteSize.x /= 3;
	spriteSize.y /= 2;
	if (state == ACTIVE) {

		Renderer::Instance()->PushSprite(PLAY_CELL_SPRITE, { spriteSize.x*0,spriteSize.y*1,spriteSize.x,spriteSize.y }, { pos.x*CELL_WIDTH, pos.y*CELL_HEIGHT + HUD_HEIGHT, CELL_WIDTH, CELL_HEIGHT });
	}
	else {
		Renderer::Instance()->PushSprite(PLAY_CELL_SPRITE, { spriteSize.x * 0,spriteSize.y * 1,spriteSize.x,spriteSize.y }, { pos.x*CELL_WIDTH, pos.y*CELL_HEIGHT + HUD_HEIGHT, 0, 0 });
	}
}

