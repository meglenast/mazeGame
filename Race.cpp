#include "Race.h"

Race::Race(RACE_CHOICE choice/*, int x_coord, int y_coord*/) :
	race(choice)
	//position(x_coord, y_coord)
{}

//public:

/*
const Coordinates& Race::getPosition()const
{
	return position;
}
*/

RACE_CHOICE Race::getRace()const
{
	return race;
}
/*
void Race::setPosition(int x_coord, int y_coord)
{
	position.setX(x_coord);
	position.setY(y_coord);
}
*/