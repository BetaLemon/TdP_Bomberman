#pragma once
#include <vector>
#include "Point.h"

using namespace std;

enum Celltype {RIGID,BREAKEABLR,SKATES,HELMET,FLOOR};
struct Cell {
	//Sprite
	Celltype type;
	Point pos;
};

class Map {
private:
	vector<vector<Cell>> grid;
public:
	//blockSprites ??
	Map();
	~Map();
	void Update();
	void Draw();
	Cell getCell(int x, int y) { return grid[x][y]; }
};