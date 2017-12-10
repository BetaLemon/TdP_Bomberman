#pragma once

#include "Scene.h"

class Ranking : public Scene {
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