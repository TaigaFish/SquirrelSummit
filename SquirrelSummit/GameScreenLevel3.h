#pragma once
#ifndef _GAMESCREENLEVEL3_H
#define _GAMESCREENLEVEL3_H

#include "GameScreenLevel.h"
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_events.h"
#include "Commons.h"
#include "GameScreen.h"
#include "LoadingZone.h"

class LockedDoor;
class PressurePlate;
class Spikes;
class Wall;
class Box;
class GameScreenLevel3 : public GameScreenLevel
{
private:
	static const unsigned int k_numWallTiles = 424;
	static const unsigned int k_numSpikeTiles = 30;

	Wall* walls[k_numWallTiles];

	bool SetUpLevel3();
	void SetUpWalls();

	LoadingZone* loading_zone_previous;

	Box* box;
	PressurePlate* plate;
	LockedDoor* door;
	Spikes* spikes[k_numSpikeTiles];
public:
	GameScreenLevel3(SDL_Renderer* renderer);
	~GameScreenLevel3();

	void Render() override;
	SCREENS Update(float deltaTime, SDL_Event e) override;
};

#endif // !_GAMESCREENLEVEL3_H