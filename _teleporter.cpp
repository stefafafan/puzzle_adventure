// Game engine includes.
#include "GraphicsManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Position.h"

// Includes.
#include "_teleporter.h"
#include "_player.h"

//PRIVATE
//PROTECTED
//PUBLIC
_teleporter::_teleporter()
{
	LogManager &lm = LogManager::getInstance();
	ResourceManager &resource_manager = ResourceManager::getInstance();

	//Set up teleporter sprite
	Sprite *p_temp_sprite = resource_manager.getSprite("teleporter");
	if (!p_temp_sprite) 
	{
		lm.writeLog("teleporter::teleporter(): Warning! Sprite '%s' not found", "teleporter");
	}
	else 
	{
		//If sprite is not found, set sprite for this object
		setSprite(p_temp_sprite); 
		setSpriteSlowdown(4);		
	}
	//Set to type teleporter
	setType("teleporter");
	//Create a position (0,0) and set teleporter to that position
	Position pos(0,0);
	setPosition(pos);
	//Set solidity of teleporter
	setSolidness(HARD);
	//Set altitude of teleporter
	setAltitude(2);
};
_teleporter::_teleporter(Position p)
{
	//Invoke Managers
	LogManager &lm = LogManager::getInstance();
	ResourceManager &resource_manager = ResourceManager::getInstance();

	//Set up teleporter sprite
	Sprite *p_temp_sprite = resource_manager.getSprite("teleporter");
	if (!p_temp_sprite) 
	{
		lm.writeLog("teleporter::teleporter(): Warning! Sprite '%s' not found", "teleporter");
	}
	else 
	{
		//If sprite is not found, set sprite for this object
		setSprite(p_temp_sprite); 
		setSpriteSlowdown(4);		
	}
	//Set to type teleporter
	setType("teleporter");
	//Set position of teleporter to given Position p
	setPosition(p);
	//Set solidity of teleporter
	setSolidness(HARD);
	//Set altitude of teleporter
	setAltitude(2);
};

_teleporter::~_teleporter(){};

int _teleporter::eventHandler(Event *p_e)
{
	/*
	if(p_e->getType() == COLLISION_EVENT)
	{
		LogManager &log_manager = LogManager::getInstance();
		log_manager.writeLog("Teleporter Collision");
		//Creates a collision based on the recieved event
		EventCollision *p_collision_event = static_cast <EventCollision *> (p_e);
		//Send new collison to the hit function
		if(p_collision_event->getObject1->getType() == "player"||
			p_collision_event->getObject2->getType() == "player")
		{
			//LOAD NEXT LEVEL
		}
	}
	*/
};