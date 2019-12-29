#include "Enchanter.h"

Enchanter::Enchanter(RACE_CHOICE race/*, int x_coord, int y_coord*/) :
	Race(race/*, x_coord, y_coord*/)
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
	Coordinates curr_move = moovingPath->front();
	moovingPath->pop();
	return curr_move;
}