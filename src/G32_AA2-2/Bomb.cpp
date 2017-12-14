#include "Bomb.h"

Bomb::Bomb() {
	timer = 0.0f;
	state = DESACTIVE;
}

void Bomb::Init(Vector2 _pos) {
	pos = _pos;
	timer = 0.0f;
	state = ACTIVE;
}

void Bomb::Update() {
	if (state == ACTIVE) {
		timer += 0.01f;
	}
}

void Bomb::Draw() {
	if (state = ACTIVE) {
		//Draw
	}
}