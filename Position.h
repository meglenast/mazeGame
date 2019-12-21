#pragma once

#include "Race.h"
#include "Monster.h"

enum POS_TYPE
{
	EMPTY = 0,
	BLOCKED,
	START,
	PORTAL
};

class Position
{
private:
	Race* character;
	Monster* monster;
	POS_TYPE position_type;
public:
	Position(Race* = nullptr, Monster* = nullptr, POS_TYPE = EMPTY);
	~Position() = default;
	Position(const Position&) = default;
	Position& operator=(const Position&) = default;
public:
	bool occupiedByMonster()const;
	bool occupiedByCharacter()const;
	POS_TYPE getPositionType()const;


};