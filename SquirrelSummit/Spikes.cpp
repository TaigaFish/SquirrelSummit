#include "Spikes.h"
#include "Collisions.h"

Spikes::Spikes(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, int offsetX, int offsetY, int lengthX, int lengthY) : Wall(renderer, imagePath, start_position, offsetX, offsetY, lengthX, lengthY) {}
Spikes::~Spikes() {}

bool Spikes::DamageUpdate(float deltaTime, SDL_Event e, GameObject* other)
{
	if (Collisions::Instance()->BoxBlock(other, this, deltaTime) != COLLISION_NONE)
	{
		return true; //collision has occured
	}
	return false; //no collision
}