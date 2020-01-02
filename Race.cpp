#include "Race.h"

Race::Race(RACE_CHOICE choice) :
	race(choice),
	movingPath(nullptr)
{}

Race::Race(const Race& other) :
	race(other.race),
	movingPath(other.movingPath)
{}

//public:

RACE_CHOICE Race::getRace()const
{
	return race;
}

void Race::setMovingPath(std::queue<Coordinates>* movingPath)
{
	this->movingPath = movingPath;
}
