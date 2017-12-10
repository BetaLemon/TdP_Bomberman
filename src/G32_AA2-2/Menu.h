#pragma once

#include "Scene.h"

class Menu : public Scene {
private:
	//buttons[5]
public:
	Menu();
	~Menu();
	void EventsHandler() override;
	void Update() override;
	void Draw() override;
};