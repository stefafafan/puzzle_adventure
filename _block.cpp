// Game engine includes.
#include "GraphicsManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Includes.
#include "_player.h"
#include "_border.h"
#include "_block.h"

#include <math.h>

_block::_block()
{
	ok = true;
	//Invoke Managers
	LogManager &lm = LogManager::getInstance();
	ResourceManager &resource_manager = ResourceManager::getInstance();

	//Set up block sprite
	Sprite *p_temp_sprite = resource_manager.getSprite("block");
	if (!p_temp_sprite) 
	{
		lm.writeLog("block::block(): Warning! Sprite '%s' not found", "block");
	}
	else 
	{
		//If sprite is not found, set sprite for this object
		setSprite(p_temp_sprite); 
		setSpriteSlowdown(4);		
	}
	//Set to type block
	setType("block");
	//Create a position (0,0) and set block to that position
	Position pos(0,0);
	setPosition(pos);
	//Set solidity of block
	setSolidness(HARD);
	//Set altitude of block
	setAltitude(2);
};
_block::~_block(){};

_block::_block(Position p)
{
	ok = true;
	//Invoke Managers
	LogManager &lm = LogManager::getInstance();
	ResourceManager &resource_manager = ResourceManager::getInstance();

	//Set up block sprite
	Sprite *p_temp_sprite = resource_manager.getSprite("block");
	if (!p_temp_sprite) 
	{
		lm.writeLog("block::block(): Warning! Sprite '%s' not found", "block");
	}
	else 
	{
		//If sprite is not found, set sprite for this object
		setSprite(p_temp_sprite); 
		setSpriteSlowdown(4);		
	}
	//Set to type block
	setType("block");
	//Set position of block to given Position p
	setPosition(p);
	//Set solidity of block
	setSolidness(HARD);
	//Set altitude of block
	setAltitude(2);
};
_block::_block(Position p, string name)
{
	ok = true;
	//Invoke Managers
	LogManager &lm = LogManager::getInstance();
	ResourceManager &resource_manager = ResourceManager::getInstance();
	//Set up block sprite with given name.
	Sprite *p_temp_sprite = resource_manager.getSprite(name);;

	if (!p_temp_sprite) 
	{
		lm.writeLog("block::block(): Warning! Sprite '%s' not found", name.c_str());
	}
	else 
	{
		//If sprite is not found, set sprite for this object
		setSprite(p_temp_sprite); 
		setSpriteSlowdown(4);		
	}
	//Set to type block
	setType("block");
	//Set position of block to given Position p
	setPosition(p);
	//Set solidity of block
	setSolidness(HARD);
	//Set altitude of block
	setAltitude(2);
};

int _block::eventHandler(Event *p_e)
{
	if(p_e->getType() == COLLISION_EVENT)
	{
		LogManager &log_manager = LogManager::getInstance();
		//Creates a collision based on the recieved event
		EventCollision *p_collision_event = static_cast <EventCollision *> (p_e);
		//Send new collison to the hit function
		hit(p_collision_event);
	}
};
void _block::hit(EventCollision *p_c)
{
	//Invoke LogManager
	LogManager &log_manager = LogManager::getInstance();
	string s1 = p_c->getObject1()->getType();
	string s2 = p_c->getObject2()->getType();
	
	if(s1 == "player" || s2 == "player")
	{
		//Create a player that points to the actual player in the collision
		_player *p_player;
		//Creats a block that points to the actual block in the collision
		_block *b_block;

		//Invoke WorldManager
		WorldManager &wm = WorldManager::getInstance();

		if(s1 == "player")
		{
			//Sets pointer to player correctly
	 		p_player = (_player*)(p_c->getObject1());
	 		//Sets pointer to block correctly
	 		b_block = (_block*) (p_c->getObject2());
		}
		else if(s2 == "player")
		{
			//Sets pointer to player correctly
			p_player = (_player*)(p_c->getObject2());
	 		//Sets pointer to block correctly
	 		b_block = (_block*) (p_c->getObject1());
		}

		//Store positions of player and block
		Position pPos = p_player -> getPosition();
		Position bPos = b_block -> getPosition();

		if(pPos.getX() == (bPos.getX() + (b_block -> getBox().getCorner().getX() - 1)) &&  ok)
		{
			//Move block right 1 position
			wm.moveObject(this, Position (bPos.getX() + 1, bPos.getY()));
			//Move player right 1 position
			wm.moveObject(p_player, Position (pPos.getX() + 1, pPos.getY()));
		}
		else if (pPos.getX() == bPos.getX() + ceil((double)b_block -> getBox().getHorizontal() / 2) && ok)
		{
			//Move block left 1 position
			wm.moveObject(this, Position (bPos.getX() - 1, bPos.getY()));
			//Move player left 1 position
			wm.moveObject(p_player, Position (pPos.getX() - 1, pPos.getY()));
		}
		else if(pPos.getY() == (bPos.getY() + (b_block -> getBox().getCorner().getY() - 1)) &&  ok)
		{
			//Move block down 1 position
			wm.moveObject(this, Position (bPos.getX(), bPos.getY() + 1));
			//Move player down 1 position
			wm.moveObject(p_player, Position (pPos.getX(), pPos.getY() + 1));
		}
		else if(pPos.getY() == bPos.getY() + ceil((double)b_block -> getBox().getVertical() / 2)  && ok)
		{
			//Move block up 1 position
			wm.moveObject(this, Position (bPos.getX(), bPos.getY() - 1));
			//Move player up 1 position
			wm.moveObject(p_player, Position (pPos.getX(), pPos.getY() - 1));
		}
		ok = true;
	}
	else if(s1 == "wall" || s2 == "wall")
	{
		//Cannot move block into wakll
		ok = false;
	}
	else if(s1 == "block" && s2 == "block")
	{
		//Cannot move block into a block
		ok = false;
	}
	else if(s1 == "_border" || s2 == "_border")
	{
		//Cannot move block into border (textbox)
		ok = false;
	}
	else if (s1 == "teleporter" || s2 == "teleporter")
	{
		// Cannot move block into teleporter
		ok = false;
	}
};