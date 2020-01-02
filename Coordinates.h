#ifndef __COORDINATES__HEADER__INCLUDED__
#define __COORDINATES__HEADER__INCLUDED__

#include <limits>

struct Coordinates
{
	int xCord;
	int yCord;

	Coordinates(int x = -1, int y = -1) :
		xCord(x),
		yCord(y)
	{}
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

	bool operator<(const PositionInformation& other)const // Used when using std:set for A* implementation
	{
		return (f_distance < other.f_distance);
	}
};

struct Asoc_pair_dist	//Helper data structure used for holding the temporary distance to a cell 
						//while the A* algorithm is performing.
{
	float f_dist;
	Coordinates coords;

	Asoc_pair_dist(float f_dist = 0.0, Coordinates coords = { 0, 0 }) :
		f_dist(f_dist),
		coords(coords)
	{}
	bool operator<(const Asoc_pair_dist& other)const // Used when using std:set for A* implementation
	{
		return (f_dist < other.f_dist);
	}
};

#endif