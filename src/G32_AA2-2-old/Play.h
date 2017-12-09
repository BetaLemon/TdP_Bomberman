#pragma once

#include "Scene.h"
#include "Map.h"
#include "Player.h"

class Play : Scene {	// !!! Falta mirar qué tipo de herencia de clases queremos (public, private, protected)
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
};