#ifndef __GAME__HEADER__INCLUDED__
#define __GAME__HEADER__INCLUDED__

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "Maze.h"



class Game
{
	Race race_choice;
	vector<Maze> levels;

public:
	Game();
public:
	void initGame();


	void printLevels();
private:
	void initRace();
	void initLevels();

	void bubbleSort();
	void sortLevels();
	void quickSort(int,int);
	int partition(int, int)const;

	void printRaceOptions()const;
	bool validRaceChoice(const std:: string)const;
	void setRace(const std::string);

	bool readMaze(std::ifstream&);
	void setCell(std::vector<Position>&, const char, int, int)const;
	void setRow(MAZE&, std::string, int)const;
};



#endif