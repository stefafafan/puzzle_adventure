/*_player.cpp*/
// Game engine includes.
#include "GraphicsManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "Event.h"
#include "EventStep.h"
#include "EventKeyboard.h"
#include "EventCollision.h"
#include "ObjectList.h"

// Includes.
#include "_player.h"
#include "_block.h"
#include "_wall.h"
#include "_teleporter.h"
#include "_text.h"
#include "_border.h"

#include <unistd.h>


_player::_player()
{
	//Set to type "player"
	setType("player");
	at_level = 1;
	setPersistence(true);
};
_player::_player(int x, int y, char cha)
{
	//Invoke Managers
	ResourceManager &rm = ResourceManager::getInstance();
	LogManager &lm = LogManager::getInstance();

	//Set up player sprite
	Sprite *p_temp_sprite;
	p_temp_sprite = rm.getSprite("player");
	if (!p_temp_sprite)
	{
		lm.writeLog("player::player(): Warning! Sprite '%s' not found", "player");
	} 
	else
	{
		//If sprite is not found, set sprite for this object
		setSprite(p_temp_sprite);
		setSpriteSlowdown(3);		// third speed animation
	}
	//Set to type player
	setType("player");
	//Create a position (x,y) and set player to that position
	Position pos = Position(x,y);
	setPosition(pos);
	//Set solidity of block
	setSolidness(HARD);
	//Set velocity of player
	setXVelocity(0);
	setYVelocity(0);
	//Set altitude of player
	setAltitude(2);
	//Register interest in Keyboard and Step events
	registerInterest(KEYBOARD_EVENT);
	registerInterest(STEP_EVENT);
	//Set character to draw to cha
	c = cha;
	setPersistence(true);
};
_player::_player(Position pos, char cha)
{
	//Invoke Managers
	ResourceManager &rm = ResourceManager::getInstance();
	LogManager &lm = LogManager::getInstance();

	//Set up player sprite
	Sprite *p_temp_sprite;
	p_temp_sprite = rm.getSprite("player");
	if (!p_temp_sprite)
	{
		lm.writeLog("player::player(): Warning! Sprite '%s' not found", "player");
	} 
	else
	{
		//If sprite is not found, set sprite for this object
		setSprite(p_temp_sprite);
		setSpriteSlowdown(3);		// third speed animation
	}
	//Set position to given Position p
	setPosition(pos);
	//Set solidity of block
	setSolidness(HARD);
	//Set velocity of player
	setXVelocity(0);
	setYVelocity(0);
	//Set altitude of player
	setAltitude(2);
	//Register interest in Keyboard and Step events
	registerInterest(KEYBOARD_EVENT);
	registerInterest(STEP_EVENT);
	//Set to type player
	setType("player");
	at_level = 1;
	//Set character to draw to cha
	c = cha;
	setPersistence(true);
};
_player::~_player(){};

void drawB()
{
	WorldManager &world_manager = WorldManager::getInstance();
	
	int maxX = world_manager.getBoundary().getHorizontal();
	int maxY = world_manager.getBoundary().getVertical();

	Position temp(0,0);

	//For loop to go through each position
	for(int i = 0; i < maxX; i += 1)
	{
		for(int j = 0; j < maxY; j += 1)
		{
			//Set temporary position variable to the current position the 2 for loops are at
			temp.setXY(i, j);

			//DRAW BORDER WALLS
			if(i == 0||
				j == 0 || 
				i == maxX - 1 ||
				j == maxY - 1)
			{
				new wall(temp);
			}
		}
	}
};

void _player::cleanLevel()
{
	WorldManager &world_manager = WorldManager::getInstance();
	int i;
	ObjectList ol = world_manager.getAllObjects();
	ObjectListIterator oli(&ol);
	for (oli.first(); !oli.isDone(); oli.next()) 
	{
		Object *p_o = oli.currentObject();
		if (p_o != NULL)
		{
			if (p_o -> getType() != "player")
				world_manager.markForDelete(p_o);
		}
	}
}

int _player::eventHandler(Event *p_e)
{
	//Invoke Managers
	LogManager &lm = LogManager::getInstance();
	WorldManager &wm = WorldManager::getInstance();
	
	if(p_e->getType() == STEP_EVENT)
	{
		return 1;
	}
	else if(p_e->getType() == KEYBOARD_EVENT)
	{
		//Cast event to Keyboard event
		EventKeyboard *p_keyboard_event = static_cast <EventKeyboard *> (p_e);
		//Assign movement to keys
		switch(p_keyboard_event->getKey())
		{
			case KEY_UP:
				wm.moveObject(this,Position(getPosition().getX(),
											getPosition().getY() - 1));
				break;
			case KEY_DOWN:
				wm.moveObject(this,Position(getPosition().getX(),
											getPosition().getY() + 1));
				break;
			case KEY_RIGHT:
				wm.moveObject(this,Position(getPosition().getX() + 1,
											getPosition().getY()));
				break;
			case KEY_LEFT:
				wm.moveObject(this,Position(getPosition().getX() - 1,
											getPosition().getY()));
				break;
			// Reset the currrent level.
			case 'r':
				cleanLevel();
				if (at_level == 1) level1();
				if (at_level == 2) level2();
				if (at_level == 3) level3();
				if (at_level == 4) level4();
				if (at_level == 5) level5();
				if (at_level == 10 || at_level == 99) quitGame();
				break;
			// Quit game:
			case 'q':
				at_level = 99;
				quitGame();
				break;
			case '1':
				cleanLevel();
				at_level = 1;
				level1();
				break;
			case '2':
				cleanLevel();
				at_level = 2;
				level2();
				break;
			case '3':
				cleanLevel();
				at_level = 3;
				level3();
				break;
			case '4':
				cleanLevel();
				at_level = 4;
				level4();
				break;
			case '5':
				cleanLevel();
				at_level = 5;
				level5();
				break;
			default:
				break;
		};
		return 1;
	}
	else if (p_e -> getType() == COLLISION_EVENT)
	{
		WorldManager &world_manager = WorldManager::getInstance();
  		SceneGraph &scene_graph = world_manager.getSceneGraph();
  		LogManager &log_manager = LogManager::getInstance();
  		GameManager &gm = GameManager::getInstance();
  		EventCollision *p_collision_event = static_cast <EventCollision *> (p_e);
  		string s1 = p_collision_event->getObject1()->getType();
		string s2 = p_collision_event->getObject2()->getType();

		if (s1 == "teleporter" || s2 == "teleporter")
		{
			cleanLevel();
			if (at_level == 1)
	  		{
				level2();
				at_level = 2;
			}
			else if(at_level == 2)
			{
				level3();
				at_level = 3;
			}
			else if (at_level == 3)
			{
				level4();
				at_level = 4;
			}
			else if (at_level == 4)
			{
				level5();
				at_level = 5;
			}
			else if (at_level == 5)
			{
				at_level = 10;
				quitGame();
			}
			else if (at_level == 10 || at_level == 99)
			{
				setPersistence(false);
				gm.setGameOver();
			}
		}
	}
};

int _player::getLevel()
{
	return at_level;
}

void _player::setLevel(int new_level)
{
	at_level = new_level;
}


/********************************************************************************************************************************************************

							GAME LEVELS

*********************************************************************************************************************************************************/

void _player::quitGame()
{
	WorldManager &world_manager = WorldManager::getInstance();
	//Store size of game screen
	int maxX = world_manager.getBoundary().getHorizontal();
	int maxY = world_manager.getBoundary().getVertical();
	cleanLevel();
	drawB();

	Position pos(world_manager.getBoundary().getCorner().getX() + maxX/2 - 10,
                (world_manager.getBoundary().getCorner().getY() + maxY/2 - 3));

	this -> setPosition(pos);

	pos.setXY(world_manager.getBoundary().getCorner().getX() + maxX/2 +10, (world_manager.getBoundary().getCorner().getY() + maxY/2 - 3));
	new _teleporter(pos);

	//Create a new border (used to display text)
	new _border();
	//Create text to display in border(textbox)
	if (at_level == 10) new _text("text_end");
	else new _text("text_q");
}

void _player::level1()
{
	WorldManager &world_manager = WorldManager::getInstance();

	//Store size of game screen
	int maxX = world_manager.getBoundary().getHorizontal();
	int maxY = world_manager.getBoundary().getVertical();

	//Find center position on screen
	Position pos(world_manager.getBoundary().getCorner().getX() + maxX/2,
                (world_manager.getBoundary().getCorner().getY() + maxY/2));

	this -> setPosition(pos);

	//Create a Position variable to be reused later
	Position temp(0,0);

	drawB();

	temp.setXY(maxX * 1/4, maxY * 1/4);
	new _block(temp);
	//
	temp.setXY(maxX * 3/4, maxY * 1/4);
	new _block(temp);
	//
	temp.setXY(maxX * 2/4, maxY * 1/4 - 1);
	new _block(temp);
	//
	temp.setXY(7, 7);
	new wall(temp);
	//
	temp.setXY(maxX - 7, 7);
	new wall(temp);
	
	temp .setXY(world_manager.getBoundary().getCorner().getX() + maxX/2,
                (world_manager.getBoundary().getCorner().getY() + maxY/2 - 3));
	new _teleporter(temp);

	//Create a new border (used to display text)
	new _border();
	//Create text to display in border(textbox)
	new _text("text_1");

};

void _player::level2()
{
	int i, j;
	WorldManager &world_manager = WorldManager::getInstance();

	//Store size of game screen
	int maxX = world_manager.getBoundary().getHorizontal();
	int maxY = world_manager.getBoundary().getVertical();

	Position temp(3,maxY-2);

	this -> setPosition(temp);

	drawB();

	for(i = 1; i < 9; i += 1)
	{
		for(j = 1; j < 8; j += 1)
		{
			temp.setXY(i,j);
			new wall(temp);
		}
	}

	for(i = 6; i < maxX; i += 1)
	{
		for(j = 11; j < maxY; j += 1)
		{
			temp.setXY(i,j);
			new wall(temp);
		}
	}

	temp.setXY(7,9);
	new _block(temp, "block3x3");

	for(i = 12; i <= 18; i += 1)
	{
		for(j = 2; j <= 7; j += 1)
		{
			temp.setXY(i,j);
			new wall(temp);
		}
	}

	for(i = 16; i <= 18; i += 1)
	{
		for(j = 8; j <= 10; j += 1)
		{
			temp.setXY(i,j);
			new wall(temp);
		}
	}

	temp.setXY(14,1);
	new _block(temp, "block4x1");

	temp.setXY(25,1);
	new wall(temp);
	temp.setXY(25,2);
	new wall(temp);

	for(i = 21; i <= 25; i +=1)
	{
		for(j = 2; j <= 9; j +=1)
		{
			temp.setXY(i,j);
			new wall(temp);
		}
	}

	//temp.setXY(30,5);
	//new _block(temp, "block2x1");
	//
	//temp.setXY(33,5);
	//new _block(temp, "block");

	for(i = 27; i < maxX - 3; i += 1)
	{
		for(j = 2; j <11; j += 1)
		{
			if(i % 2 == 0 && j %2 == 1)
			{
				temp.setXY(i,j);
				new _block(temp);
			}
		}
	}

	temp.setXY(maxX - 2, 6);
	new _teleporter(temp);

	//Create a new border (used to display text)
	new _border();
	//Create text to display in border(textbox)
	new _text("text_2");
};

void _player::level3()
{
	int i, j;
	WorldManager &world_manager = WorldManager::getInstance();
	LogManager &log_manager = LogManager::getInstance();


	//Store size of game screen
	int maxX = world_manager.getBoundary().getHorizontal();
	int maxY = world_manager.getBoundary().getVertical();

	drawB();

	Position temp(3, 2);
	this -> setPosition(temp);

	temp.setXY(maxX - 4, maxY - 4);
	new _teleporter(temp);

	temp.setXY(15, 5);
	new _block(temp, "block8x8");

	temp.setXY(31, 8);
	new _block(temp, "block8x8");

	temp.setXY(40, 5);
	new _block(temp, "block8x8");

	temp.setXY(maxX - 9, 5);
	new _block(temp, "block16x3");

	temp.setXY(maxX - 26, 5);
	new _block(temp, "block16x3");

	temp.setXY(maxX - 9, 10);
	new _block(temp, "block16x3");

	temp.setXY(maxX - 26, 10);
	new _block(temp, "block16x3");

	temp.setXY(maxX - 3, 8);
	new wall(temp);

	temp.setXY(maxX - 9, maxY - 7);
	new _block(temp, "block8x8");

	temp.setXY(maxX - 8, maxY - 3);
	new _block(temp, "block12x1");

	temp.setXY(maxX - 17, maxY - 3);
	new _block(temp, "block6x1");

	//Create a new border (used to display text)
	new _border();
	//Create text to display in border(textbox)
	new _text("text_3");
}

void _player::level4()
{
	int i, j;
	WorldManager &world_manager = WorldManager::getInstance();
	LogManager &log_manager = LogManager::getInstance();


	//Store size of game screen
	int maxX = world_manager.getBoundary().getHorizontal();
	int maxY = world_manager.getBoundary().getVertical();

	Position temp(maxX/2, 2);
	this -> setPosition(temp);

	drawB();

	temp.setXY(maxX/2 , 4);
	new _block(temp, "block3x3");
	temp.setXY(maxX/2 , 6);
	new _teleporter(temp);
	temp.setXY(maxX/2 , 8);
	new _block(temp, "block3x3");
	temp.setXY(maxX/2 - 2 , 6);
	new _block(temp, "block1x7");
	temp.setXY(maxX/2 + 2 , 6);
	new _block(temp, "block1x7");

	//Create a new border (used to display text)
	new _border();
	//Create text to display in border(textbox)
	new _text("text_4");
};

void _player::level5()
{
	int i, j;
	WorldManager &world_manager = WorldManager::getInstance();
	LogManager &log_manager = LogManager::getInstance();

	//Store size of game screen
	int maxX = world_manager.getBoundary().getHorizontal();
	int maxY = world_manager.getBoundary().getVertical();

	Position temp(maxX/2, 2);
	this -> setPosition(temp);

	drawB();

	for(i = 1; i < maxX - 1; i += 1)
	{
		if(i % 2 == 0)
		{
			temp.setXY(i,2);
			new _block(temp);
			temp.setXY(i,4);
			new _block(temp);
			temp.setXY(i,6);
			new _block(temp);
		}
		else if(i % 2 == 1)
		{
			temp.setXY(i,1);
			new _block(temp);
			temp.setXY(i,3);
			new _block(temp);
			temp.setXY(i,5);
			new _block(temp);
			temp.setXY(i,7);
			new _block(temp);
		}
		if(i != 1 && i != 2 && i != maxX -3 && i != maxX - 2)
		{
			temp.setXY(i,8);
			new wall(temp);
		}

	}

	temp.setXY(maxX / 2,10);
	new _teleporter(temp);

	//Create a new border (used to display text)
	new _border();
	//Create text to display in border(textbox)
	new _text("text_5");
};