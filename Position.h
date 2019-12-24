#pragma once

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
	Position(Race* = nullptr, Monster* = nullptr, POS_TYPE = UNDEFINED, const Coordinates & = { 0,0 },char = '.');
	~Position() = default;
	Position(const Position&) = default;
	Position& operator=(const Position&) = default;
public:
	bool occupiedByMonster()const;
	bool occupiedByCharacter()const;
	bool isBlocked()const;
	POS_TYPE getPositionType()const;
	Coordinates getCoordinates()const;

	void setCharacter(RACE_CHOICE);
	void setPositionType(POS_TYPE);


};