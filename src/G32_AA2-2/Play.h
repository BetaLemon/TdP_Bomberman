#pragma once

#include "Scene.h"
#include "Map.h"
#include "Player.h"
#include <string>
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include <sstream>
#include <iostream>

class Play : public Scene {
private:
	Player player1;
	Player player2;
	Map map;

	PlayerMoveAllow CanPlayerMove(Player _player);
	void InitBomb(Player _player);
	int explodeMap(Vector2 center);
	BombRange explodeRange(Vector2 center);
	void PlayerCollision(Player* p1, Player* p2);
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
};