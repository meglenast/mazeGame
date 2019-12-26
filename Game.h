#ifndef __GAME__HEADER__INCLUDED__
#define __GAME__HEADER__INCLUDED__

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "Maze.h"



class Game
{
	RACE_CHOICE race_choice;
	vector<Maze> levels;

public:
	Game();
public:
	void initGame();
	void initRace();


	void printLevels();
private:
	void startGame();
	void initLevels();

	void bubbleSort();
	void sortLevels();
	void mergeSort(vector<Maze>&, int, int);
	void merge(vector<Maze>&, int, int, int);


	bool readMaze(std::ifstream&);
	void setCell(std::vector<Position>&, const char, int, int, unsigned&)const;
	void setRow(MAZE&, std::string, int,unsigned&)const;


	void printRaceOptions()const;
	bool validRaceChoice(const std::string)const;
	void setRace(const std::string);
	void setPlayersCell(RACE_CHOICE);
};



#endif