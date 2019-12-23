#pragma once

#include <vector>
#include <queue>

#include "Position.h"
using std::vector;



typedef vector<vector<Position>> MAZE;
typedef vector<vector<bool>> VISITED_MATRIX;

const int DIRECTIONS = 4;

//const Coordinates START = { 1,1 };
//const Coordinates PORTAL = { n,m};

//int DX[] = {-1,0,0,1};
//int DY[] = {0,-1,1,0};



class Maze
{
private:
	MAZE field;
	int x_size;
	int y_size;
	int monsters;

	//Coordinates start;  //idk if i need this t.t
	//Coordinates portal;// this too
public:
	Maze();
	Maze(const MAZE&, int, int, int);
	~Maze() = default;
	Maze(const Maze&) = default;
	Maze& operator=(const Maze&) = default;
public:
	bool validMazeCheck()const;

	bool BFS()const;
private:
	//void initField();
	
	//bool BFS()const;
	bool markedUnvisited(VISITED_MATRIX&)const;
	bool validCellCheck(int,int)const;

};