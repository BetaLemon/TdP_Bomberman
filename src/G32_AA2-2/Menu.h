#pragma once

#include "Scene.h"
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include <sstream>

struct Button {
	Text text;
	int x, y;
};

class Menu : public Scene {
private:
	Button play1Butt, play2Butt, exitButt, rankButt, musicButt;
	Rect mouseDown;
public:
	Menu();
	~Menu();
	void EventsHandler() override;
	void Update() override;
	void Draw() override;
};