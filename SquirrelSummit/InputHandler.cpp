#include "InputHandler.h"

//initialise instance to nullptr
InputHandler* InputHandler::m_instance = nullptr;

InputHandler::InputHandler() {}
InputHandler::~InputHandler()
{
	delete m_instance;
	m_instance = nullptr;
}

InputHandler* InputHandler::Instance()
{
	if (!m_instance)
	{
		m_instance = new InputHandler;
	}

	return m_instance;
}

Input InputHandler::PollForInput(SDL_Event e)
{
	switch (e.type)
	{
	case SDL_JOYBUTTONDOWN:
		switch (e.jbutton.button)
		{
		case 13: //up
			return INPUT_DOWN_UP;
		case 16: //down
			return INPUT_DOWN_DOWN;
		case 14: //left
			return INPUT_DOWN_LEFT;
		case 15: //right
			return INPUT_DOWN_RIGHT;
		case 12: //side b
		case 4: //a
		case 9: //b
			return INPUT_DOWN_JUMP;
		case 11: //side a
		case 2: //y
		case 7: //x
			return INPUT_DOWN_DASH;
		case 8: //L2
		case 5: //L1
			return INPUT_DOWN_FLOAT;
		case 6: //R2
		case 1: // R1
			return INPUT_DOWN_THROW;
		}
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			return INPUT_DOWN_UP;
		case SDLK_DOWN:
			return INPUT_DOWN_DOWN;
		case SDLK_LEFT:
			return INPUT_DOWN_LEFT;
		case SDLK_RIGHT:
			return INPUT_DOWN_RIGHT;
		case SDLK_SPACE:
			return INPUT_DOWN_JUMP;
		}
		break;
	case SDL_JOYBUTTONUP:
		switch (e.jbutton.button)
		{
		case 13: //up
			return INPUT_UP_UP;
		case 16: //down
			return INPUT_UP_DOWN;
		case 14: //left
			return INPUT_UP_LEFT;
		case 15: //right
			return INPUT_UP_RIGHT;
		case 12: //side b
		case 4: //a
		case 9: //b
			return INPUT_UP_JUMP;
		case 11: //side a
		case 2: //y
		case 7: //x
			return INPUT_UP_DASH;
		case 8: //L2
		case 5: //L1
			return INPUT_UP_FLOAT;
		case 6: //R2
		case 1: // R1
			return INPUT_UP_THROW;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			return INPUT_UP_UP;
		case SDLK_DOWN:
			return INPUT_UP_DOWN;
		case SDLK_LEFT:
			return INPUT_UP_LEFT;
		case SDLK_RIGHT:
			return INPUT_UP_RIGHT;
		case SDLK_SPACE:
			return INPUT_UP_JUMP;
		}
		break;
	}
	return INPUT_NONE;
}