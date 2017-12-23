#pragma once

#include "Scene.h"
#include "Map.h"
#include "Player.h"
//#include "Collisions.h"

class Play : public Scene {
private:
	Player player1;
	Player player2;
	Map map;
	//map
	//pointsFont
	//lifeSprite
public:
	Play();
	Play(int level);
	~Play();
	void EventsHandler() override;
	void Update() override;
	void Draw() override;
	bool Collision(Rect _player, Rect other);
	void CheckPlayersCollisions(Player _player);
	void CalculateBombExplosions(Player _player);
	void InitBomb(Player _player);
};