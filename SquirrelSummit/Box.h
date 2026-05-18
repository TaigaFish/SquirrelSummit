#pragma once
#ifndef _BOX_H
#define _BOX_H

#include "GameObject.h"
#include <string>
#include "../packages/sdl2.nuget.2.30.0/build/native/include/SDL_events.h"
#include "Commons.h"
#include "GameScreen.h"

class Box : public GameObject
{
public:
	Box(SDL_Renderer* renderer, Vector2D startLocation, std::string imagePath = "Images/Crate.png", int offsetX = 0, int offsetY = 0, int lengthX = 16, int lengthY = 16);
	~Box();

	bool Update(float deltaTime, SDL_Event e, GameObject* other);
};

#endif // !_BOX_H