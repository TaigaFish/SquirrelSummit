#pragma once
#ifndef _SPIKES_H
#define _SPIKES_H

#include "Wall.h"

class Spikes : public Wall
{
public:
	Spikes(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, int offsetX = 0, int offsetY = 0, int lengthX = 16, int lengthY = 16);
	~Spikes();
	bool DamageUpdate(float deltaTime, SDL_Event e, GameObject* other); //different so standard update can be used for objects that don't take damage
};

#endif // !_SPIKES_H