#pragma once
#ifndef _GAMESCREENMENU_H
#define _GAMESCREENMENU_H

#include "GameScreen.h"
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_events.h"
#include "Commons.h"
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_render.h"
class Wall;
class GameText;
class Texture2D;
class Character;
class GameScreenMenu : public GameScreen
{
public:
	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();
	SCREENS Update(float deltaTime, SDL_Event e) override;
	void Render() override;
private:
	static const unsigned int k_numWallTiles = 282;

	bool SetUpMenu();
	Texture2D* m_background_texture;
	Wall* walls[k_numWallTiles];
	GameText* title;
	GameText* subText;
	Character* my_character;
};

#endif // !_GAMESCREENMENU_H