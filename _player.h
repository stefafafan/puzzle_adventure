/*_player.h*/

#ifndef _player_h_
#define _player_h_

#include "Object.h"

class _player : public Object
{
	private:
		// Store which level the player is currently in.
		int at_level;
	protected:
	public:
		char c;	//Character to represent player
		_player();
		virtual ~_player();
		_player(int x, int y, char c);	//Create a player at position (x,y), draw with character c
		_player(Position pos, char c);	//Create a player at position p, draw with character c
		int eventHandler(Event *p_e);	//Handles Keyboard events
		int getLevel(); // Get the current level the player is in.
		void setLevel(int new_level);
		void level1();
		void level2();
		void level3();
		void level4();
		void level5();
		void cleanLevel();
		void quitGame();
};
#endif
