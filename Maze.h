#pragma once

#include <vector>
#include <queue>

#include <iostream>
#include <ctime>
#include <windows.h>

#include "Position.h"
//#include "Graph.h"
#include "Monster.h"

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
	RACE_CHOICE race_choice;
	unsigned free_cells;
	Position* character_pos;
	std::vector<Position*> monsters_list;

public:
	Maze();
	Maze(const MAZE&, int, int, int);
	~Maze() = default;
	Maze(const Maze&);
	Maze& operator=(const Maze&);
	
public:
	bool validMazeCheck()const;
	bool operator<(const Maze&)const;

	inline int getSize()const;
	inline int getMonsters()const;

	void print()const;//move after in private

	void startLevel(RACE_CHOICE);

	void setFreeCells(unsigned);

private:

	void startGame();

	void restartLevel();
	void setStartAndPortal();
	void setCharacterCell(RACE_CHOICE);

	//void generatePathEnchanter()const;
	//void genetatePathMagus()const;

	void spawnMonsters();
	void spawnMonster();
	bool canSpawn(unsigned, unsigned)const;
	void addMonsterToList(int,int);
	void changeMonsterList(int, int, int, int);
	void moveMonsters();
	void moveMonster(int, int, int, int);

	bool BFS()const;
	void BFS(std::queue<Coordinates>&)const;
	bool markedUnvisited(VISITED_MATRIX&)const;
	bool validCellCheck(int,int)const;

	void printRow(int, char, char)const;
	void printExtraRow(char, char)const;
	void printCell(const Position&, char)const;
	void printMaze()const;

	void blockCells();
	void blockCell();
	void chooseNumCellsToBlock(unsigned&);
	void chooseWhichCellsToBlock(unsigned);
	bool validCellsToBlock(unsigned)const;
	

	bool validCoordinates(int, int)const;
	bool alreadyBlocked(int, int)const;
	bool alreadyOccupied(int, int)const;

	void buildGraph()const;

	//del after:
	void printQ(std::queue<Coordinates>&)const;

};