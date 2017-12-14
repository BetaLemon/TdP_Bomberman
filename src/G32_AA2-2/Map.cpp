#include "Map.h"
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include <sstream>

#include <iostream>

Map::Map() {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 13; j++) {
			Cell tmp;
			tmp.pos.x = i; tmp.pos.y = j;
			tmp.type = Celltype::FLOOR;
			grid[i][j] = tmp;
		}
	}
}

Map::Map(int level) {

	rapidxml::xml_document<> config;
	std::ifstream file(PATH_FILES + "config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	config.parse<0>(&content[0]);

	rapidxml::xml_node<> *root = config.first_node("Game");	// <Game>
	rapidxml::xml_node<> *lvl;
	rapidxml::xml_node<> *currentCell;

	switch (level) {
	case 1:
		// Leer mapa 1 xml
		lvl = root->first_node("Level");
		/*if (lvl->first_attribute("id")->value() != "1") {
			lvl = lvl->next_sibling();
		}*/
			// destructible
		currentCell = lvl->first_node("Destructible");
		for (rapidxml::xml_node<> *wallNode = currentCell->first_node("Wall"); wallNode; wallNode = wallNode->next_sibling()) {			
			int i = atoi(wallNode->first_attribute("i")->value());
			int j = atoi(wallNode->first_attribute("j")->value());
			grid[i][j] = Cell{ Celltype::DESTRUCTIBLE, {i,j} };
		}
			// fixed
		currentCell = lvl->first_node("Fixed");
		for (rapidxml::xml_node<> *wallNode = currentCell->first_node("Wall"); wallNode; wallNode = wallNode->next_sibling()) {
			int i = atoi(wallNode->first_attribute("i")->value());
			int j = atoi(wallNode->first_attribute("j")->value());
			grid[i][j] = Cell{ Celltype::FIXED,{ i,j } };
		}
		break;
	case 2:
		// Leer mapa 2 xml
		/*lvl = root->first_node("Level");
		std::cout << lvl->first_attribute("id")->value() << std::endl;
		system("pause");
		if(lvl->first_attribute("id")->value() != "2") {
			lvl = lvl->next_sibling();
		}*/

		lvl = root->last_node("Level");

		// destructible
			currentCell = lvl->first_node("Destructible");
		for (rapidxml::xml_node<> *wallNode = currentCell->first_node("Wall"); wallNode; wallNode = wallNode->next_sibling()) {
			int i = atoi(wallNode->first_attribute("i")->value());
			int j = atoi(wallNode->first_attribute("j")->value());
			grid[i][j] = Cell{ Celltype::DESTRUCTIBLE,{ i,j } };
		}
			// fixed
		currentCell = lvl->first_node("Fixed");
		for (rapidxml::xml_node<> *wallNode = currentCell->first_node("Wall"); wallNode; wallNode = wallNode->next_sibling()) {
			int i = atoi(wallNode->first_attribute("i")->value());
			int j = atoi(wallNode->first_attribute("j")->value());
			grid[i][j] = Cell{ Celltype::FIXED,{ i,j } };
		}
		break;
	default:;
	}
}

Map::~Map() {

}