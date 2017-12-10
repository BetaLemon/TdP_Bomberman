#pragma once

#include "Scene.h"
#include "Map.h"
#include "Player.h"

class Play : public Scene {
private:
	Player player1;
	Player player2;
	Map map;
	//map
	//pointsFont
	//lifeSprite
public:
	Play(int level);
	~Play();
	void EventsHandler() override;
	void Update() override;
	void Draw() override;

	void CheckPlayersCollisions(Player _player);
};