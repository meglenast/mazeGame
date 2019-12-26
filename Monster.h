#pragma once

#include "Coordinates.h"

enum MOVING_DIRECTION
{
	UP = 0,
	LEFT,
	DOWN,
	RIGHT
};

class Monster
{
private:
	Coordinates position;
	enum MOVING_DIRECTION next_direction;
public:
	Monster(int= -1, int = -1, MOVING_DIRECTION = UP);
	Monster(const Monster&) = default;
	Monster& operator=(const Monster&) = default;
	~Monster() = default;
public:
	void changeDirection();
	void changeCoordinates(int,int);

	const Coordinates& nextCoordinates()const;
	const Coordinates& getCoordinates()const;
};