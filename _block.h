#ifndef __BLOCK_H
#define __BLOCK_H

#include "Object.h"
#include "Event.h"
#include "EventCollision.h"

class _block : public Object
{
	private:
		bool ok;	//Used to confirm that the block is moveable and should be drawn
	protected:
	public:
		_block();	//Create a new block at 0,0
		~_block();
		_block(Position p);	//Create a new block at position p
		_block(Position p, string name);
		int eventHandler(Event *p_e);	//Handle collision events (and any others in necessary)
		void hit(EventCollision *p_c);	//Make sure that block is moveable and move it to the correct position
};

#endif