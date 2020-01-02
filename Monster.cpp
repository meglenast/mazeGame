#include "Monster.h"

Monster::Monster(int x_coord, int y_coord, bool isBlocked, MOVING_DIRECTION direction) :
	position(x_coord, y_coord),
	isBlocked(isBlocked),
	next_direction(direction)
{}

//public:

void Monster::changeDirection()									 //Changes the moving direction when reached a hidrance cell or a blocked by the player cell
{
	if (next_direction == UP)
			next_direction = LEFT;
	else if (next_direction == LEFT)
			next_direction = DOWN;
	else if (next_direction == DOWN)
			next_direction = RIGHT;
	else if (next_direction == RIGHT)
			next_direction = UP;
}

void Monster::changeCoordinates(int x_coord,int y_coord)
{
	position.xCord = x_coord;
	position.yCord = y_coord;
}

const Coordinates& Monster::nextCoordinates()const
{
	if (next_direction == UP)
	{
		int new_x = position.xCord - 1;
		int new_y = position.yCord;
		return Coordinates(new_x, new_y);
	}
	else if (next_direction == LEFT)
	{
		int new_x = position.xCord;
		int new_y = position.yCord - 1;
		return Coordinates(new_x, new_y);
	}
	else if (next_direction == DOWN)
	{
		int new_x = position.xCord + 1;
		int new_y = position.yCord;
		return Coordinates(new_x, new_y);
	}
	else if (next_direction == RIGHT)
	{
		int new_x = position.xCord;
		int new_y = position.yCord + 1;
		return Coordinates(new_x, new_y);
	}
}

const Coordinates& Monster::getCoordinates()const
{
	return position;
}

bool Monster::blocked()const
{
	return isBlocked;
}