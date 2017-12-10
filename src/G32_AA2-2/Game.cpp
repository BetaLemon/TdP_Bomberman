#include "Game.h"

Game::Game() {
	currentScene = new Menu();
	gameState = GameState::MENU;
}

Game::~Game(){
	delete currentScene;
}

void Game::Run() {
	while (gameState != GameState::EXIT) {
		switch (currentScene->getSceneState()) {
		case SceneState::RUNNING:
			currentScene->EventsHandler();
			currentScene->Update();
			currentScene->Draw();
			break;
		case SceneState::GOTO_MENU:
			delete currentScene;
			currentScene = nullptr;
			currentScene = new Menu();
			gameState = GameState::MENU;
			break;
		case SceneState::GOTO_PLAY1:
			delete currentScene;
			currentScene = nullptr;
			currentScene = new Play(1);
			gameState = GameState::PLAY;
			break;
		case SceneState::GOTO_PLAY2:
			delete currentScene;
			currentScene = nullptr;
			currentScene = new Play(2);
			gameState = GameState::PLAY;
			break;
		case SceneState::GOTO_RANKING:
			delete currentScene;
			currentScene = nullptr;
			currentScene = new Ranking();
			gameState = GameState::RANKING;
			break;
		case SceneState::GOTO_SETSCORE:
			delete currentScene;
			currentScene = nullptr;
			currentScene = new Ranking();
			gameState = GameState::RANKING;
			break;
		case SceneState::EXIT:
			delete currentScene;
			gameState = GameState::EXIT;
			break;
		default:;
		}
	}
}