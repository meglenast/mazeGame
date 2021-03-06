#ifndef __MAZE__HEADER__INCLUDED__
#define __MAZE__HEADER__INCLUDED__

#include <vector>
#include <queue>
#include <stack>
#include <set>

#include <ctime>

#include "InterfaceFunctions.h"
#include "Position.h"

typedef std::vector<std::vector<Position>> MAZE;
typedef std::vector<std::vector<bool>> VISITED_MATRIX;
typedef std::vector<std::vector<PositionInformation>> POSITIONS_INFO;

const int DIRECTIONS = 4;
const int ONE_STEP   = 1;

const char WHITE_SQUARE = 0xDB;
const char BLACK_SQUARE = 0xFF;

const int DX[] = { -1,0,0,1 };
const int DY[] = { 0,-1,1,0 };

class Maze
{
private:
	MAZE field;
	size_t x_size;
	size_t y_size;
	int monsters;
	RACE_CHOICE race_choice;
	unsigned free_cells;
	Position* character_pos;
	std::queue<Coordinates>* movingPath;
	std::vector<Position*> monsters_list;
public:
	Maze();
	Maze(const MAZE&, int, int, int);
	Maze(const Maze&) = default;
	Maze& operator=(const Maze&) = default;
	~Maze();
public:
	bool startLevel(RACE_CHOICE);

	bool validMazeCheck()const;
	bool operator<(const Maze&)const;

	inline int getSize()const;
	inline int getMonsters()const;

	void setFreeCells(unsigned);

private:

	bool startGame();

	bool haveReachedPortal()const;
	bool killedByMonster()const;

	void restartLevel();
	void setStartAndPortal();
	void setCharacterCell(RACE_CHOICE);

	void spawnMonsters();
	void spawnMonster();
	bool canSpawn(unsigned, unsigned)const;
	void addMonsterToList(int,int);
	void changeMonsterList(int, int, int, int);
	void moveMonsters();
	void moveMonster(int, int, int, int);

	void generateMagusPath();
	void DFS_iterative();		//Used for generating a path in maze going in a streight direction until a hidrance is met.
	void changeMagusDirection(MOVING_DIRECTION&)const;

	void generateEnchanterPath();
	void pathTracing(const POSITIONS_INFO&);
	void aStarAlgorithm();		//Use for generating the shortest path using additional heuristics for calculating the current shortest path to the sink node.
	void initPositionInfo(POSITIONS_INFO&)const;
	double calcHdist(int, int)const;

	void moveCharacter();

	bool BFS()const;
	bool markedUnvisited(VISITED_MATRIX&)const;
	bool validCellCheck(int,int)const;

	void print()const;
	void printColNumbers()const;
	void printRow(int, char, char)const;
	void printExtraRow(char, char)const;
	void printCell(const Position&, char)const;

	void blockCells();
	void blockCell();
	void chooseNumCellsToBlock(unsigned&);
	void chooseWhichCellsToBlock(unsigned);
	bool validCellsToBlock(unsigned)const;
	
	bool validCoordinates(int, int)const;
	bool alreadyBlocked(int, int)const;
	bool alreadyOccupied(int, int)const;
	bool isPortal(int, int)const;
	bool noEscapeCell(int x_coord, int y_coord)const;
};

#endif