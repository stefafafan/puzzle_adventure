# makefile by Stefan Alexander and Maxwell Perlman
#
# Makefile for development of game using Dragonfly
#
# 'make' to build executable
# 'make depend' to generate new dependency list
# 'make clean' to remove all constructed files
#
# Variables of interest:
#   GAMESRC is the source code files for the game being developed
#   GAME is the game main() source
#   DEBUG can be set to -DDEBUG to enable various debug flags
#

CC= g++ 
PLATFORM= -DCYGWIN		# uncomment for cygwin
#PLATFORM= -DMACOS  		# uncomment for macos
LDFLAGS= -lncurses -lrt	# uncomment linux/cygwin
#LDFLAGS= -lncurses 		# uncomment for macos
INCPATH= include		# path to engine includes
ENG= lib/libdragonfly.a		# dragonfly engine
GAMESRC= 	_wall.cpp \
			_player.cpp \
			_border.cpp \
			_block.cpp \
			_text.cpp \
			_teleporter.cpp
GAME= game.cpp
EXECUTABLE= puzzle_adventure		
OBJECTS= $(GAMESRC:.cpp=.o)

all: $(EXECUTABLE) Makefile

$(EXECUTABLE): $(ENG) $(OBJECTS) $(GAME) $(GAMESRC)
	$(CC) $(GAME) $(OBJECTS) $(ENG) -o $@ -I$(INCPATH) $(LDFLAGS) 

.cpp.o: 
	$(CC) -c $(DEBUG) -I$(INCPATH) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) core dragonfly.log Makefile.bak *~

depend: 
	makedepend *.cpp 2> /dev/null

# DO NOT DELETE

_block.o: _player.h _border.h _block.h /usr/include/math.h
_block.o: /usr/include/sys/reent.h /usr/include/_ansi.h /usr/include/newlib.h
_block.o: /usr/include/sys/config.h /usr/include/machine/ieeefp.h
_block.o: /usr/include/sys/features.h /usr/include/sys/_types.h
_block.o: /usr/include/machine/_types.h /usr/include/machine/_default_types.h
_block.o: /usr/include/sys/lock.h
_border.o: _border.h
_player.o: _player.h _block.h _wall.h _teleporter.h
_teleporter.o: _teleporter.h _player.h
_text.o: _text.h
_wall.o: _wall.h
game.o: _player.h _wall.h _border.h _block.h _text.h _teleporter.h
