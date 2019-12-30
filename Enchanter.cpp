#include "Enchanter.h"

Enchanter::Enchanter(RACE_CHOICE race) :
	Race(race)
{}
Enchanter::Enchanter(const Race& other) :
	Race(other)
{}
Enchanter& Enchanter::operator=(const Enchanter& other)
{
	if (this != &other)
	{
		Race::operator=(other);
	}
	return *this;
}

//public:

const Coordinates& Enchanter::getMove()
{
	Coordinates curr_move = movingPath->front();
	movingPath->pop();
	return curr_move;
}
