#pragma once
#ifndef _WALL_H
#define _WALL_H

#include "GameObject.h"
#include <string>
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_events.h"
#include "Commons.h"
#include "GameScreen.h"

class Wall : public GameObject
{
public:
	Wall(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, int offsetX = 0, int offsetY = 0, int lengthX = 16, int lengthY = 16);
	~Wall();

	virtual bool Update(float deltaTime, SDL_Event e, GameObject* other);
};

#endif // !_WALL_H