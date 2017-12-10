#pragma once
#include <vector>

enum Celltype {RIGID,BREAKEABLR,SKATES,HELMET,FLOOR};
struct Cell {
	//Sprite
	Celltype type;
};

class Map {
private:
	std::vector<std::vector<Cell>> grid;
public:
	//blockSprites ??
	Map();
	~Map();
	void Update();
	void Draw();
	Cell getCell(int x, int y) { return grid[x][y]; }
};