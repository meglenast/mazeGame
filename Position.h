#pragma once

#include "Race.h"
#include "Monster.h"

enum POS_TYPE
{
	EMPTY = 0,
	BLOCKED,
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
	POS_TYPE getPositionType()const;
	Coordinates getCoordinates()const;


};