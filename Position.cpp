#include "Position.h"

Position::Position(Race* race, Monster* monster, POS_TYPE pos_type, const Coordinates& coords, char symbol) :
	character(race),
	monster(monster),
	position_type(pos_type),
	coordinates(coords),
	symbol(symbol)
{}

Position::~Position()
{
	if (!monster)
		delete monster;
	if (!character)
		delete character;
	monster   = nullptr;
	character = nullptr;
}
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
	return (position_type == BLOCKED || position_type == BLOCKED_BY_USER);
}
POS_TYPE Position::getPositionType()const
{
	return position_type;
}

Coordinates Position::getCoordinates()const
{
	return coordinates;
}

Monster* Position::getMonster()const
{
	return monster;
}

const Monster& Position::getMonsterByReference()const
{
	return *monster;
}

Race& Position::getCharacter()const
{
	return *character;
}

void Position::setCharacter(RACE_CHOICE choice)
{
	if (choice == ENCHANTER)
	{
		character = new Enchanter(ENCHANTER);
	}
	else
	{
		character = new Magus(MAGUS);
	}
}

void Position::setMonsterByReference(const Monster& monster)
{
	this->monster = new Monster(monster);
}
void Position::setCharacterByReference(const Race& character)
{
	if (character.getRace() == MAGUS)
		this->character = new Magus(character);
	else if (character.getRace() == ENCHANTER)
		this->character = new Enchanter(character);
}

void Position::setMonster(unsigned x_coord, unsigned y_coord, bool isBlocked)
{
	monster = new Monster(x_coord, y_coord, isBlocked);
}

bool Position::monsterIsBlocked()const
{
	return monster->blocked();
}

void Position::setPositionType(POS_TYPE pos_type)
{
	position_type = pos_type;
}

void Position::addMovingPath(std::queue<Coordinates>* moovingPath)
{
	character->setMovingPath(moovingPath);
}

const Coordinates& Position::getCharacterMove()const
{
	return character->getMove();
}

void Position::removeMonster()
{
	if (!monster)
	{
		delete monster;
		monster = nullptr;
	}
	monster = nullptr;
}

void Position::removeCharacter()
{
	if (!character)
	{
		delete character;
		character = nullptr;
	}
	character = nullptr;
}