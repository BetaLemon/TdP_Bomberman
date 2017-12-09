#pragma once

enum class SceneState{/*...*/};

class Scene {
protected:
	// background
	SceneState sceneState;
public:
	Scene();
	~Scene();
	virtual void EventsHandler() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};