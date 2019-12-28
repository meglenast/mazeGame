#pragma once

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
private:
	RACE_CHOICE race;
	//Coordinates position;
public:
	Race(RACE_CHOICE = INVALID/*, int = -1, int = -1*/);
	virtual ~Race() = default;
	Race(const Race&) = default;
	Race& operator=(const Race&) = default;
public:

	//virtual void generateMovingPath() = 0;
	//const Coordinates& getPosition()const;
	RACE_CHOICE getRace()const;


	//void setPosition(int, int);
private:
	/*
	 ...
	*/
};
