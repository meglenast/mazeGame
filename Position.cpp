#include "Position.h"

Position::Position(Race* race, Monster* monster, POS_TYPE pos_type, const Coordinates& coords, char symbol) :
	character(race),
	monster(monster),
	position_type(pos_type),
	coordinates(coords),
	symbol(symbol)
{}

//public:

bool Position::occupiedByMonster()const
{
	return monster != nullptr;
}

bool Position::occupiedByCharacter()const
{
	return character != nullptr;
}

POS_TYPE Position::getPositionType()const
{
	return position_type;
}

Coordinates Position::getCoordinates()const
{
	return coordinates;
}