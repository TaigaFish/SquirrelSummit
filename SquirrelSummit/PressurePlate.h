#pragma once
#ifndef _PRESSUREPLATE_H
#define _PRESSUREPLATE_H

#include "GameObject.h"

class LockedDoor;
class PressurePlate : public GameObject
{
private:
	LockedDoor* door;

	void LockDoor();
	void UnlockDoor();
public:
	PressurePlate(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LockedDoor* door, int offsetX = 0, int offsetY = 0, int lengthX = 0, int lengthY = 0);
	~PressurePlate();

	bool Update(float deltaTime, SDL_Event e, GameObject* other);
};

#endif // !_PRESSUREPLATE_H