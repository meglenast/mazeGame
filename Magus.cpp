#include "Magus.h"

Magus::Magus(RACE_CHOICE race) :
	Race(race)
{}
Magus::Magus(const Race& other) :
	Race(other)
{}
Magus& Magus::operator=(const Magus& other)
{
	if (this != &other)
	{
		Race::operator=(other);
	}
	return *this;
}

//public:

const Coordinates& Magus::getMove()
{
	Coordinates curr_move = movingPath->front();
	movingPath->pop();
	return curr_move;
}
