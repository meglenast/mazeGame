#pragma once

#include <vector>

#include "Position.h"
using std::vector;


typedef vector<vector<Position>> MAZE;

class Maze
{
private:
	MAZE field;
	Coordinates start;  //idk if i need this t.t
	Coordinates portal;
public:
	Maze() = default;
	~Maze() = default;
	Maze(const Maze&) = default;
	Maze& operator=(const Maze&) = default;
private:
	void initField();

};