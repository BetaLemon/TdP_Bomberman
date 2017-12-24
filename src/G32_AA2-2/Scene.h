#pragma once

#include "Renderer.h"
#include "Music.h"

enum class SceneState { RUNNING, EXIT, GOTO_PLAY1, GOTO_PLAY2, GOTO_RANKING, GOTO_MENU, GOTO_SETSCORE, TOGGLE_MUSIC };

class Scene {
protected:
	// background
	SceneState sceneState;
	Music music;
	bool musicRunning;
public:
	Scene();
	~Scene();
	virtual void EventsHandler() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	SceneState getSceneState() { return sceneState; }
};