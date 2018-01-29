#pragma once
#include "Types.h"
#include "Renderer.h"

enum BombState{ACTIVE,WAITING};

struct BombRange { int up, down, left, right; };	// 0 just center. 1 means +1 from center. 2 means +2 from center (in the corresponding directions).

class Bomb {
	private:
		Vector2 pos;
		BombState state;
		bool exploded;
		float timer;
		Vector2 bomb_s;
		Vector2 explos_s;
		int explosionStage;
		BombRange range;
		//sprite
	public:
		Bomb();
		void Init(Vector2 pos);
		void Update();
		void Draw();
		float getTimer() { return timer; }
		Vector2 getGridPos();
		void setState(BombState _state);
		BombState getState() { return state; }
		bool hasExploded();
		void setRange(BombRange _range);
};