#pragma once

#include <vector>
#include <queue>

#include <iostream>
#include <windows.h>

#include "Position.h"
using std::vector;



typedef vector<vector<Position>> MAZE;
typedef vector<vector<bool>> VISITED_MATRIX;

const int DIRECTIONS = 4;

const char WHITE_SQUARE = 0xDB;
const char BLACK_SQUARE = 0xFF;

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
	Maze(const Maze&);
	Maze& operator=(const Maze&);
public:
	bool validMazeCheck()const;
	bool operator<(const Maze&)const;
	//bool BFS()const;
	inline int getSize()const;
	inline int getMonsters()const;
	void print()const;
	void printRow(int, char, char)const;
	void printExtraRow(char, char)const;
	void printCell(const Position&, char)const;
	void printMaze()const;
private:
	//void initField();
	
	bool BFS()const;
	bool markedUnvisited(VISITED_MATRIX&)const;
	bool validCellCheck(int,int)const;

};