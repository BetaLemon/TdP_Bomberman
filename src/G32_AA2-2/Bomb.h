#pragma once
#include "Types.h"
#include "Renderer.h"

enum BombState{ACTIVE,WAITING};

class Bomb {
	private:
		Vector2 pos;
		BombState state;
		float timer;
		//sprite
	public:
		Bomb();
		void Init(Vector2 pos);
		void Update();
		void Draw();
		float getTimer() { return timer; }
		void setState(BombState _state);
		BombState getState() { return state; }
};