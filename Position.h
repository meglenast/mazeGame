#ifndef __POSITION__HEADER__INCLUDED__
#define __POSITION__HEADER__INCLUDED__

#include "Enchanter.h"
#include "Magus.h"
#include "Monster.h"

enum POS_TYPE
{
	EMPTY = 0,
	BLOCKED,
	BLOCKED_BY_USER,
	START,
	PORTAL,
	UNDEFINED
};

class Position
{
private:
	Race* character;
	Monster* monster;
	POS_TYPE position_type;
	Coordinates coordinates;
	char symbol;

public:
	Position(Race* = nullptr, Monster* = nullptr, POS_TYPE = EMPTY, const Coordinates & = { 0,0 },char = '.');
	~Position();
	Position(const Position&) = default;
	Position& operator=(const Position&) = default;

public:

	bool occupiedByMonster()const;
	bool occupiedByCharacter()const;

	bool isBlocked()const;
	POS_TYPE getPositionType()const;
	Coordinates getCoordinates()const;

	Monster* getMonster()const;
	const Monster& getMonsterByReference()const;
	void removeMonster();
	void setMonster(unsigned, unsigned, bool);
	void setMonsterByReference(const Monster&);
	void setPositionType(POS_TYPE);
	bool monsterIsBlocked()const;

	void removeCharacter();
	void setCharacter(RACE_CHOICE);
	void setCharacterByReference(const Race&);
	Race& getCharacter()const;

	void addMovingPath(std::queue<Coordinates>*);
	const Coordinates& getCharacterMove()const;
};

#endif