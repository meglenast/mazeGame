#include "Position.h"

Position::Position(Race* _character, Monster* _monster, POS_TYPE _position_type, Coordinates coordinates) :
	character(_character),
	monster(_monster),
	position_type(_position_type),
	coordinates(coordinates)
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