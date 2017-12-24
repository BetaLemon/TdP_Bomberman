#pragma once

#include "Scene.h"
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include <sstream>

class Menu : public Scene {
private:
	Button play1Butt, play2Butt, exitButt, rankButt, musicButt;
	Rect mouseDown;
	bool checkClick(Rect button, int x, int y);
public:
	Menu();
	~Menu();
	void EventsHandler() override;
	void Update() override;
	void Draw() override;
};