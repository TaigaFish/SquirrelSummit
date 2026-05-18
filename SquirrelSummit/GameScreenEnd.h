#pragma once
#ifndef _GAMESCREENEND_H
#define _GAMESCREENEND_H

#include "GameScreen.h"

class Wall;
class GameText;
class Texture2D;
class Character;
class GameScreenEnd : public GameScreen
{
public:
	GameScreenEnd(SDL_Renderer* renderer);
	~GameScreenEnd();

	void Render();
private:
	static const unsigned int k_numWallTiles = 50;

	Wall* walls[k_numWallTiles];
	Character* my_character;
	GameText* endTextLine1;
	GameText* endTextLine2;
	Texture2D* m_background_texture;

	void SetUpEnd();
};

#endif // !_GAMESCREENEND_H