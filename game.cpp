// Game engine includes.
#include "ResourceManager.h"
#include "LogManager.h"
#include "GameManager.h"
#include "WorldManager.h"
#include "InputManager.h"
#include "GraphicsManager.h"

// Include files.
#include "_player.h"
#include "_wall.h"
#include "_border.h"
#include "_block.h"
#include "_text.h"
#include "_teleporter.h"

int main()
{
	//Invoke all managers
	GameManager &game_manager = GameManager::getInstance();
	game_manager.startUp();
	ResourceManager &resource_manager = ResourceManager::getInstance();
	LogManager &log_manager = LogManager::getInstance();
	WorldManager &world_manager = WorldManager::getInstance();
	GraphicsManager &graphics_manager = GraphicsManager::getInstance();

	//Add all sprites to resource manager
	resource_manager.loadSprite("sprites/player.txt", "player");
	resource_manager.loadSprite("sprites/wall.txt", "wall");
	resource_manager.loadSprite("sprites/border.txt", "border");
	resource_manager.loadSprite("sprites/block.txt", "block");
	resource_manager.loadSprite("sprites/block2x1.txt", "block2x1");
	resource_manager.loadSprite("sprites/block3x3.txt", "block3x3");
	resource_manager.loadSprite("sprites/block4x1.txt", "block4x1");
	resource_manager.loadSprite("sprites/block1x7.txt", "block1x7");
	resource_manager.loadSprite("sprites/block8x8.txt", "block8x8");
	resource_manager.loadSprite("sprites/block6x1.txt", "block6x1");
	resource_manager.loadSprite("sprites/block12x1.txt", "block12x1");
	resource_manager.loadSprite("sprites/block16x3.txt", "block16x3");	
	resource_manager.loadSprite("sprites/teleporter.txt", "teleporter");
	resource_manager.loadSprite("sprites/text_1.txt", "text_1");
	resource_manager.loadSprite("sprites/text_2.txt", "text_2");
	resource_manager.loadSprite("sprites/text_3.txt", "text_3");
	resource_manager.loadSprite("sprites/text_4.txt", "text_4");
	resource_manager.loadSprite("sprites/text_5.txt", "text_5");
	resource_manager.loadSprite("sprites/text_q.txt", "text_q");
	resource_manager.loadSprite("sprites/text_end.txt", "text_end");


	//Store size of game screen
	int maxX = world_manager.getBoundary().getHorizontal();
	int maxY = world_manager.getBoundary().getVertical();

	//Find center position on screen
	Position pos(world_manager.getBoundary().getCorner().getX() + maxX/2,
                (world_manager.getBoundary().getCorner().getY() + maxY/2));

	_player *pl = new _player(pos, 'x');
	pl -> level1();
	pl -> setLevel(1);

	game_manager.run();
	game_manager.shutDown();
	
	return 0;
};
