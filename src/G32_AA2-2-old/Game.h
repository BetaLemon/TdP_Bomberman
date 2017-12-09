#pragma once

#include "Scene.h"

enum class GameState { MENU, GAME, RANKING, EXIT};

class Game {
private:
	Scene * currentScene;
public:
	Game();
	~Game();
	void Run();
};