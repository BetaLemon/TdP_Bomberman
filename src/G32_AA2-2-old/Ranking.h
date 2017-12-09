#pragma once

#include "Scene.h"

class Ranking : Scene {	// !!! Herencia de classes
private:
	//records;
	//mode;
public:
	Ranking();
	~Ranking();
	void EventsHandler() override;
	void Update() override;
	void Draw() override;
	void Save();
	void Load();
};