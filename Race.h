#ifndef __RACE__HEADER__INCLUDED__
#define __RACE__HEADER__INCLUDED__

//del
//#include <iostream>
#include <queue>

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
	std::queue<Coordinates>* movingPath;
public:
	Race(RACE_CHOICE = INVALID);
	Race(const Race&);
	Race& operator=(const Race&) = default;
	virtual ~Race() = default;

public:
	virtual const Coordinates& getMove() = 0;

	void setMovingPath(std::queue<Coordinates>*);

	RACE_CHOICE getRace()const;
};

#endif