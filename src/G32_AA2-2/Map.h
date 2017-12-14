#pragma once
#include <vector>	// Aún hace falta??
#include "Constants.h"
#include "Types.h"

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
	Cell getCell(int x, int y) { return grid[x][y]; }
};