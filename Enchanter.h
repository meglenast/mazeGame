#ifndef __ENCHANTER__HEADER__INCLUDED__
#define __ENCHANTER__HEADER__INCLUDED__

#include "Race.h"

class Enchanter : public Race
{
public:
	Enchanter(RACE_CHOICE = ENCHANTER);
	Enchanter(const Race&);
	Enchanter& operator=(const Enchanter&);
	~Enchanter() = default;
public:
	const Coordinates& getMove();
};

#endif