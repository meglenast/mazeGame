#pragma once

#include <limits>

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

struct PositionInformation		//Helper data  structure used for holding additional information for the cell 
								//while A* algortihm is performing.
{
	float f_distance;
	float g_distance;
	float h_distance;

	int adjecent_xCoord;
	int adjecent_yCoord;

	PositionInformation(float f = FLT_MAX, float g = FLT_MAX, float h = FLT_MAX, int adj_x = -1, int adj_y = -1) :
		f_distance(f),
		g_distance(g),
		h_distance(h),
		adjecent_xCoord(adj_x),
		adjecent_yCoord(adj_y)
	{}

	void setInfo(float new_fDist, float new_gDist, float new_hDist, int new_adjX, int new_adjY)
	{
		f_distance = new_fDist;
		g_distance = new_gDist;
		h_distance = new_hDist;
		adjecent_xCoord = new_adjX;
		adjecent_yCoord = new_adjY;
	}
};

struct Asoc_pair_dist	//Helper data structure used for holding the temporary distance to a cell 
						//while the A* algorithm is performing.
{
	float f_dist;
	Coordinates coords;

	Asoc_pair_dist(float f_dist, Coordinates coords) :
		f_dist(f_dist),
		coords(coords)
	{}

	bool operator<(const Asoc_pair_dist& other)const
	{
		return (f_dist < other.f_dist);
	}
};