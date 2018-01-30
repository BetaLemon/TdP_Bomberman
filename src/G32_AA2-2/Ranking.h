#pragma once

#include "Scene.h"
#include <fstream>
#include <iostream>
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include <sstream>

struct Entry { std::string name; int points; };

class Ranking : public Scene {
private:
	Entry ranking[10];
	bool writeMode;
	Rect mouseDown;
	Button backButton;
	int playScore;
	std::string playerName;
	bool finishedInput;

	bool checkClick(Rect button, int x, int y);
	void FillEmptyBinary(std::string path);
	void ReadBinary(std::string path);
	void WriteBinary(std::string path);
	int getPlayScore(std::string path);
public:
	Ranking(bool mode);
	~Ranking();
	void EventsHandler() override;
	void Update() override;
	void Draw() override;
};