#pragma once

class Coordinates
{
private:
	int xCord;
	int yCord;
public:
	
	Coordinates(int x = -1, int y = -1) :
		xCord(x),
		yCord(y)
	{}

	Coordinates(const Coordinates& other) :
		xCord(other.xCord),
		yCord(other.yCord)
	{}

	Coordinates& operator=(const Coordinates& other)
	{
		if (this != &other)
		{
			xCord = other.xCord;
			yCord = other.yCord;
		}
		return *this;
	}

	int getX()const { return xCord; }
	int getY()const { return yCord; }
	void setX(int x) { xCord = x; }
	void setY(int y) { yCord = y; }
};