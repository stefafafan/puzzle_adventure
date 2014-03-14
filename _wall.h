#ifndef __WALL_H
#define __WALL_H

#include "Object.h"

class wall : public Object
{
	public:
	wall();			// Create wall at (0, 0).
	wall(Position p);	// Create wall at position p.
	~wall();			// Wall destructor.
};

#endif // __WALL_H
 