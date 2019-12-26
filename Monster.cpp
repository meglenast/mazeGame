#include "Monster.h"

Monster::Monster(int x_coord, int y_coord, MOVING_DIRECTION direction) :
	position(x_coord, y_coord),
	next_direction(direction)
{}

//public:

void Monster::changeDirection() //have reached a hidrance cell or a blocked by the player cell
{
	if (next_direction == UP)
		next_direction = LEFT;
	else if (next_direction == LEFT)
		next_direction = DOWN;
	else if (next_direction == DOWN)
		next_direction = RIGHT;
	else
		next_direction = UP;
}

void  Monster::changeCoordinates(int x_coord,int y_coord)
{
	position.setX(x_coord);
	position.setY(y_coord);
}

const Coordinates& Monster::nextCoordinates()const
{
	if (next_direction == UP)
		return (Coordinates(position.getX(), position.getY() - 1));
	else if (next_direction == LEFT)
		return (Coordinates(position.getX() - 1, position.getY()));
	else if (next_direction == DOWN)
		return (Coordinates(position.getX(), position.getY() + 1));
	else
		return (Coordinates(position.getX() + 1, position.getY()));
}

const Coordinates& Monster::getCoordinates()const
{
	return position;
}
