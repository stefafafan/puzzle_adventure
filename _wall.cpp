// Game engine includes.
#include "LogManager.h"
#include "ResourceManager.h"

// Includes.
#include "_wall.h"

wall::wall()
{
	// Get instances of necessary managers.
	LogManager &lm = LogManager::getInstance();
	ResourceManager &resource_manager = ResourceManager::getInstance();

	// Set up wall sprite.
	Sprite *p_temp_sprite = resource_manager.getSprite("wall");
	if (!p_temp_sprite) 
	{
		lm.writeLog("wall::wall(): Warning! Sprite '%s' not found", "wall");
	}
	else 
	{
		// If sprite is found, set sprite for this object.
		setSprite(p_temp_sprite); 	
	}

	// Set type of wall.
	setType("wall");

	// Default constructor sets position to 0.
	Position pos(0, 0);
	setPosition(pos);
	
	// Collides with anything (player or block).
	setSolidness(HARD);
	setAltitude(2);
};

wall::wall(Position p)
{
	// Get instances of necessary managers.
	LogManager &lm = LogManager::getInstance();
	ResourceManager &resource_manager = ResourceManager::getInstance();

	// Set up wall sprite.
	Sprite *p_temp_sprite = resource_manager.getSprite("wall");
	if (!p_temp_sprite) 
	{
		lm.writeLog("wall::wall(): Warning! Sprite '%s' not found", "wall");
	} 
	else 
	{
		// If sprite is found, set sprite for this object.
		setSprite(p_temp_sprite); 	
	}

	// Set type of wall.
	setType("wall");

	// Set position to given position.
	setPosition(p);

	// Collides with anything (player or block).
	setSolidness(HARD);
	setAltitude(2);
};

// Deconstructor does nothing.
wall::~wall(){};
