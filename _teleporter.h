#ifndef __TELEPORTER_H
#define __TELEPORTER_H

#include "Object.h"
#include "Event.h"
#include "EventCollision.h"

class _teleporter : public Object
{
	private:
	protected:
	public:
		_teleporter();	//Create a new teleporter at 0,0
		~_teleporter();
		_teleporter(Position p);	//Create a new teleporter at position p
		int eventHandler(Event *p_e);	//Handle collision events (and any others in necessary)
};

#endif