#ifndef __text_H
#define __text_H

#include "ViewObject.h"

class _text : public ViewObject
{
public:
	_text();		// Create text to show in message box.
	_text(string name);
	~_text();	// Text destructor.
	void draw();	// Draw itself.
};

#endif // __text_H
