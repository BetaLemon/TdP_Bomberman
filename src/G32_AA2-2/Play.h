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

class Play : public Scene {
private:
	Player player1;
	Player player2;
	Map map;

	PlayerMoveAllow CanPlayerMove(Player _player);
	void PlayerCollision(Player p1, Player p2);
	void InitBomb(Player _player);
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