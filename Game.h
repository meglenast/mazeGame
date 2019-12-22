#ifndef __GAME__HEADER__INCLUDED__
#define __GAME__HEADER__INCLUDED__

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "Maze.h"

const char* MAZE_FILE = "mazeFile.txt";

class Game
{
	Race race_choice;
	vector<Maze> levels;

public:
	Game();
public:
	void initGame();
private:
	void initRace();
	void initLevels();

	void printRaceOptions()const;
	bool validRaceChoice(const std:: string)const;
	void setRace(const std::string);

	void readMaze(std::ifstream&);
	void setCell(MAZE&, char, int, int)const;
};



#endif