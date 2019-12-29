#pragma once

#include <queue>

//del
#include <iostream>

#include "Coordinates.h"

enum RACE_CHOICE
{
	INVALID = 0,
	ENCHANTER,
	MAGUS,
	RACE_COUNTER
};

class Race
{
protected:
	RACE_CHOICE race;
	std::queue<Coordinates>* moovingPath;
	//Coordinates position;
public:
	Race(RACE_CHOICE = INVALID);
	Race(const Race&);
	Race& operator=(const Race&) = default;
	virtual ~Race() = default;
public:

	//virtual void generateMovingPath() = 0;
	//const Coordinates& getPosition()const;
	void setMoovingPath(std::queue<Coordinates>*);
	virtual const Coordinates& getMove()=0;

	RACE_CHOICE getRace()const;


	//void setPosition(int, int);
private:
	/*
	 ...
	*/
};
