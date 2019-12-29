#include "Race.h"

Race::Race(RACE_CHOICE choice) :
	race(choice),
	moovingPath(nullptr)
{}

Race::Race(const Race& other) :
	race(other.race),
	moovingPath(other.moovingPath)
{}

//public:

void Race::setMoovingPath(std::queue<Coordinates>* moovingPath)
{
	this->moovingPath = moovingPath;
}

RACE_CHOICE Race::getRace()const
{
	return race;
}
