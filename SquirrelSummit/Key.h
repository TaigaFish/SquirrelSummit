#pragma once
#ifndef _KEY_H
#define _KEY_H

#include "GameObject.h"

class LockedDoor;
class Character;
class Key : public GameObject
{
private:
	LockedDoor* door;
	Character* player;

	void UnlockDoor();
public:
	Key(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LockedDoor* door, Character* character, int offsetX = 0, int offsetY = 0, int lengthX = 0, int lengthY = 0);
	~Key();

	bool Update(float deltaTime, SDL_Event e) override;
};

#endif // !_KEY_H