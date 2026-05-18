#pragma once
#ifndef _LOADINGZONE_H
#define _LOADINGZONE_H

#include "GameObject.h"

class Character;
class LoadingZone : public GameObject
{
public:
	LoadingZone(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, Character* character, int offsetX = 0, int offsetY = 0, int lengthX = 0, int lengthY = 0);
	~LoadingZone();

	virtual bool Update(float deltaTime, SDL_Event e) override;
private:
	Character* player;
};

#endif // !_LOADINGZONE_H