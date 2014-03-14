// Game engine includes.
#include "WorldManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "EventStep.h"

// Include files.
#include "_border.h"

_border::_border()
{
	// Get instances of necessary managers.
	LogManager &log_manager = LogManager::getInstance();
	ResourceManager &resource_manager = ResourceManager::getInstance();
	WorldManager &world_manager = WorldManager::getInstance();

	// Set up border sprite.
	Sprite *p_temp_sprite = resource_manager.getSprite("border");
	if (!p_temp_sprite) 
	{
		log_manager.writeLog("_border::_border(): Warning! Sprite '%s' not found", "border");
	} 
	else
	{
		// If sprite is found, set sprite for this object.
		setSprite(p_temp_sprite);
	}

	// Set type of border.
	setType("_border");

	// Make sure it collides with others so game objects don't pass through message box.
	setSolidness(HARD);
	setAltitude(2);

	// Set position to middle center of the terminal.
	Position pos(world_manager.getBoundary().getCorner().getX() + world_manager.getBoundary().getHorizontal()/2,
              ( world_manager.getBoundary().getCorner().getY() + world_manager.getBoundary().getVertical()/2) + 6);
  	setPosition(pos);
};

// Destructor does nothing.
_border::~_border(){};
