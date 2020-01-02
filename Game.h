#ifndef __GAME__HEADER__INCLUDED__
#define __GAME__HEADER__INCLUDED__

#include <string>
#include <iostream>
#include <fstream>

#include "Maze.h"
#include "InterfaceFunctions.h"

class Game
{
	RACE_CHOICE race_choice;
	std::vector<Maze> levels;

public:
	Game();
	Game(const Game&) = default;
	Game& operator=(const Game&) =default;
	~Game() = default;
public:
	void initGame();
private:
	void startGame();
	void initLevels();
	void initRace();

	void sortLevels();
	void mergeSort(std::vector<Maze>&, int, int);
	void merge(std::vector<Maze>&, int, int, int);
	void bubbleSort(std::vector<Maze>&);

	bool readMaze(std::ifstream&);
	void setCell(std::vector<Position>&, const char, int, int, unsigned&)const;
	void setRow(MAZE&, std::string, int,unsigned&)const;

	bool validRaceChoice(const std::string)const;
	void setRace(const std::string);
};

#endif