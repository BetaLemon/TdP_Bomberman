#pragma once
#include <vector>	// Aún hace falta??
#include "Constants.h"
#include "Types.h"
#include "Renderer.h"

using namespace std;

enum Celltype {FIXED,DESTRUCTIBLE,SKATES,HELMET,FLOOR};
struct Cell {
	//Sprite
	Celltype type;
	Vector2 pos;
};

class Map {
private:
	//vector<vector<Cell>> grid;
	Cell grid[GRID_WIDTH][GRID_HEIGHT];
public:
	//blockSprites ??
	Map();
	Map(int level);
	~Map();
	void Update();
	void Draw();
 	Cell getCell(Vector2 pos) { return grid[pos.x][pos.y]; }
	Vector2 getCellPixPos(Vector2 pos);
};