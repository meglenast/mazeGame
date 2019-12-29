#ifndef __ENCHANTER__HEADER__INCLUDED__
#define __ENCHANTER__HEADER__INCLUDED__

#include "Race.h"

class Enchanter : public Race
{
public:
	Enchanter(RACE_CHOICE = ENCHANTER/*, int = -1, int = -1*/);
	Enchanter(const Race&);
	Enchanter& operator=(const Enchanter&);

public:
	const Coordinates& getMove();
	//virtual void generateMovingPath();
	//bool validMove(int, int)const;
	//bool canReach(int, int)const;

private:
};


#endif