#pragma once
#ifndef _GAMESCREENLEVEL2_H
#define _GAMESCREENLEVEL2_H

#include "GameScreenLevel.h"
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_events.h"
#include "Commons.h"
#include "GameScreen.h"
#include "LoadingZone.h"

class LockedDoor;
class Key;
class Wall;
class GameScreenLevel2 : public GameScreenLevel
{
public:
	GameScreenLevel2(SDL_Renderer* renderer, SCREENS lastScreen);
	~GameScreenLevel2();

	void Render() override;
	SCREENS Update(float deltaTime, SDL_Event e) override;
private:
	static const unsigned int k_numWallTiles = 340;

	Wall* walls[k_numWallTiles];

	bool SetUpLevel2();

	LoadingZone* loading_zone_previous;

	Key* key;
	LockedDoor* door;
};

#endif // !_GAMESCREENLEVEL2_H