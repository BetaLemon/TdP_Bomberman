#pragma once

#include "Scene.h"
#include "Menu.h"
#include "Play.h"
#include "Ranking.h"

enum class GameState { MENU, PLAY, RANKING, EXIT};

class Game {
private:
	Scene * currentScene;
	GameState gameState;
public:
	Game();
	~Game();
	void Run();
};