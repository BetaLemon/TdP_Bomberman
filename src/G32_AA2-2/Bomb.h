#pragma once
#include "Types.h"

enum BombState{ACTIVE,DESACTIVE};

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
		BombState getState() { return state; }
};