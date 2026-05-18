#pragma once
#ifndef _LOCKEDDOOR_H
#define _LOCKEDDOOR_H

#include "GameObject.h"

class Character;
class LockedDoor : public GameObject
{
public:
	LockedDoor(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, Vector2D end_offset, Character* character, int offsetX = 0, int offsetY = 0, int lengthX = 0, int lengthY = 0);
	~LockedDoor();

	bool isLocked = true;

	bool Update(float deltaTime, SDL_Event e) override;
private:
	bool Open(float deltaTime);
	bool Close(float deltaTime);
	bool Move(float deltaTime, Vector2D startPos, Vector2D endPos);
	bool isOpening = true;
	bool isClosing = false;
	Vector2D startPosition;
	Vector2D endPosition;
	Vector2D m_maxVelocity;

	Character* player;
};

#endif // !_LOCKEDDOOR_H