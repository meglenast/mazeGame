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
	bool isBlocked;
	enum MOVING_DIRECTION next_direction;
public:
	Monster(int= 0, int = 0, bool = false, MOVING_DIRECTION = UP);
	Monster(const Monster&);
	Monster& operator=(const Monster&);
	~Monster() = default;
public:
	void changeDirection();
	void changeCoordinates(int,int);

	const Coordinates& nextCoordinates()const;
	const Coordinates& getCoordinates()const;
	bool blocked()const;
};