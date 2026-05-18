#pragma once
#ifndef _INPUTHANDLER_H
#define _INPUTHANDLER_H
#include "Commons.h"
#include <SDL.h>

class InputHandler
{
public:
	~InputHandler();

	static InputHandler* Instance();

	Input PollForInput(SDL_Event e);
private:
	InputHandler();

	static InputHandler* m_instance;
};

#endif // !_INPUTHANDLER_H