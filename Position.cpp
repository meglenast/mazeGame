#include "Position.h"

Position::Position(Race* race, Monster* monster, POS_TYPE pos_type, const Coordinates& coords, char symbol) :
	character(race),
	monster(monster),
	position_type(pos_type),
	coordinates(coords),
	symbol(symbol)
{}


//destructor!!!

//public:

bool Position::occupiedByMonster()const
{
	return monster != nullptr;
}

bool Position::occupiedByCharacter()const
{
	return character != nullptr;
}

bool Position::isBlocked()const
{
	return position_type == BLOCKED;
}

POS_TYPE Position::getPositionType()const
{
	return position_type;
}

Coordinates Position::getCoordinates()const
{
	return coordinates;
}

void Position::setCharacter(RACE_CHOICE choice)
{
	if (choice == ENCHANTER)
	{
		character = new Enchanter;
	}
	else
	{
		character = new Magus;

	}
}

void Position::setMonster(unsigned x_coord, unsigned y_coord)
{
	monster = new Monster(x_coord, y_coord);
}

void Position::setPositionType(POS_TYPE pos_type)
{
	position_type = pos_type;
}