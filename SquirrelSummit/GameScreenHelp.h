#pragma once
#ifndef _GAMESCREENHELP_H
#define _GAMESCREENHELP_H

#define NUM_WALL_TILES 282

#include "GameScreen.h"
class Wall;
class GameText;
class Texture2D;
class Character;
class GameScreenHelp : public GameScreen
{
public:
	GameScreenHelp(SDL_Renderer* renderer, bool onEvercade);
	~GameScreenHelp();
	SCREENS Update(float deltaTime, SDL_Event e) override;
	void Render() override;
private:
	bool SetUpHelp();
	Texture2D* m_background_texture;
	Wall* walls[NUM_WALL_TILES];
	GameText* helpText1;
	GameText* helpText2;
	GameText* subText;
	Character* my_character;
	const char* line1;
	const char* line2;
};

#endif // !_GAMESCREENHELP_H