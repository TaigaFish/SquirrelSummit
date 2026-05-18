#include "GameScreen.h"

#include "Commons.h"
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_events.h"

GameScreen::GameScreen(SDL_Renderer* renderer) 
{
	m_renderer = renderer;
	next_screen = SCREEN_NONE;
	prev_screen = SCREEN_NONE;
	current_screen = SCREEN_NONE;
}
GameScreen::~GameScreen()
{
	m_renderer = nullptr;
}

void GameScreen::Render(){}
SCREENS GameScreen::Update(float deltaTime, SDL_Event e)
{
	return next_screen;
}