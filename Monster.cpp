#include "Monster.h"

Monster::Monster(int x_coord, int y_coord, bool isBlocked, MOVING_DIRECTION direction) :
	position(x_coord, y_coord),
	isBlocked(isBlocked),
	next_direction(direction)
{}

Monster::Monster(const Monster& other) :
	position(other.position),
	isBlocked(other.isBlocked),
	next_direction(other.next_direction)
{}

Monster& Monster:: operator=(const Monster& other)
{
	if (this != &other)
	{
		position = other.position;
		isBlocked = other.isBlocked;
		next_direction = other.next_direction;
	}
	return *this;
}

//public:

void Monster::changeDirection()									 //cChanges the moving direction when reached a hidrance cell or a blocked by the player cell
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
	position.setX(x_coord);
	position.setY(y_coord);
}

const Coordinates& Monster::nextCoordinates()const
{
	if (next_direction == UP)
	{
		int new_x = position.getX() - 1;
		int new_y = position.getY();
		return Coordinates(new_x, new_y);
	}
	else if (next_direction == LEFT)
	{
		int new_x = position.getX();
		int new_y = position.getY() - 1;
		return Coordinates(new_x, new_y);
	}
	else if (next_direction == DOWN)
	{
		int new_x = position.getX() + 1;
		int new_y = position.getY();
		return Coordinates(new_x, new_y);
	}
	else if (next_direction == RIGHT)
	{
		int new_x = position.getX();
		int new_y = position.getY() + 1;
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