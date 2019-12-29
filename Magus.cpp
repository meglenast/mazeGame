#include "Magus.h"

Magus::Magus(RACE_CHOICE race/*, int x_coord, int y_coord*/) :
	Race(race/*, x_coord, y_coord*/)
{}

const Coordinates& Magus::getMove()
{
	Coordinates curr_move = moovingPath->front();
	moovingPath->pop();
	return curr_move;
}