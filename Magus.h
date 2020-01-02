#ifndef __MAGUS__HEADER__INCLUDED__
#define __MAGUS__HEADER__INCLUDED__

#include "Race.h"

class Magus : public Race
{
public:
	Magus(RACE_CHOICE = MAGUS);
	Magus(const Race&);
	Magus& operator=(const Magus&);

public:
	const Coordinates& getMove();
};

#endif