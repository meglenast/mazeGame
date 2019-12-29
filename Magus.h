#ifndef __MAGUS__HEADER__INCLUDED__
#define __MAGUS__HEADER__INCLUDED__

#include "Race.h"

class Magus : public Race
{
public:
	Magus(RACE_CHOICE = MAGUS/*, int = -1, int = -1*/);

public:
	const Coordinates& getMove();
	//bool validMove(int, int)const;
	//bool canReach(int, int)const;
	//virtual void generateMovingPath();
private:
};


#endif