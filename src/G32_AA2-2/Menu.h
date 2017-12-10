#pragma once

#include "Scene.h"

struct Button {
	Text text;
	int x, y;
};

class Menu : public Scene {
private:
	Button play1Butt, play2Butt, exitButt, rankButt;
	Rect mouseDown;
public:
	Menu();
	~Menu();
	void EventsHandler() override;
	void Update() override;
	void Draw() override;
};