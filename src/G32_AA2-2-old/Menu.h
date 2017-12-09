#pragma once

#include "Scene.h"

class Menu : Scene {	// !!! Herencia de classes!
private:
	//buttons[5]
public:
	Menu();
	~Menu();
	void EventsHandler() override;
	void Update() override;
	void Draw() override;
};