#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include "GameScreenLevel.h"

#define NUM_WALL_TILES 282

class Wall;
class GameScreenLevel1 : public GameScreenLevel
{
public:
	GameScreenLevel1(SDL_Renderer* renderer, SCREENS last_screen);
	~GameScreenLevel1();

	void Render() override;
	SCREENS Update(float deltaTime, SDL_Event e) override;
private:
	Wall* walls[NUM_WALL_TILES];
	bool SetUpLevel1();
};

#endif // !_GAMESCREENLEVEL1_H