// Game engine includes.
#include "WorldManager.h"
#include "ResourceManager.h"
#include "LogManager.h"

// Include files.
#include "_text.h"

_text::_text()
{
	// Get instances of necessary managers.
	LogManager &log_manager = LogManager::getInstance();
	ResourceManager &resource_manager = ResourceManager::getInstance();
	WorldManager &world_manager = WorldManager::getInstance();

	// Set up text sprite.
	Sprite *p_temp_sprite = resource_manager.getSprite("text");
	if (!p_temp_sprite) 
	{
		log_manager.writeLog("_text::_text(): Warning! Sprite '%s' not found", "text");
	} 
	else
	{
		// If sprite is found, set sprite for this object.
		setSprite(p_temp_sprite);
	}

	// Set type of text.
	setType("text");

	// Set position to middle center of the terminal (same as border).
	Position pos(world_manager.getBoundary().getCorner().getX() + world_manager.getBoundary().getHorizontal()/2,
              ( world_manager.getBoundary().getCorner().getY() + world_manager.getBoundary().getVertical()/2) + 6);
  	setPosition(pos);
};

_text::_text(string name)
{
	// Get instances of necessary managers.
	LogManager &log_manager = LogManager::getInstance();
	ResourceManager &resource_manager = ResourceManager::getInstance();
	WorldManager &world_manager = WorldManager::getInstance();

	// Set up text sprite.
	Sprite *p_temp_sprite = resource_manager.getSprite(name);
	if (!p_temp_sprite) 
	{
		log_manager.writeLog("_text::_text(): Warning! Sprite '%s' not found", "text");
	} 
	else
	{
		// If sprite is found, set sprite for this object.
		setSprite(p_temp_sprite);
	}

	// Set type of text.
	setType("text");

	// Set position to middle center of the terminal (same as border).
	Position pos(world_manager.getBoundary().getCorner().getX() + world_manager.getBoundary().getHorizontal()/2,
              ( world_manager.getBoundary().getCorner().getY() + world_manager.getBoundary().getVertical()/2) + 6);
  	setPosition(pos);
}

// Destructor does nothing.
_text::~_text(){};

// Call the Object's draw since this is a ViewObject, not a regular Object.
void _text::draw()
{
	Object::draw();
}
