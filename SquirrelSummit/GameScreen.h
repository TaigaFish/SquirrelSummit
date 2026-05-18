#pragma once
#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

struct SDL_Renderer;
enum SCREENS;
union SDL_Event;
class GameScreen
{
public:
	GameScreen(SDL_Renderer* renderer);
	virtual ~GameScreen();

	virtual void Render();
	virtual SCREENS Update(float deltaTime, SDL_Event e);
protected:
	SDL_Renderer* m_renderer;

	SCREENS next_screen;
	SCREENS prev_screen;
	SCREENS current_screen;
};

#endif // !_GAMESCREEN_H