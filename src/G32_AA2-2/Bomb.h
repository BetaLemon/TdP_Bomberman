#pragma once
#include "Point.h"

enum BombState{ACTIVE,DESACTIVE};

class Bomb {
	private:
		Point pos;
		BombState state;
		float timer;
		//sprite
	public:
		Bomb();
		void Init(Point pos);
		void Update();
		void Draw();
		float getTimer() { return timer; }
		BombState getState() { return state; }
};