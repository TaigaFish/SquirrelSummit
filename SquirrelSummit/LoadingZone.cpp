#include "LoadingZone.h"

#include "Collisions.h"
#include "Character.h"

LoadingZone::LoadingZone(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, Character* character, int offsetX, int offsetY, int lengthX, int lengthY) : GameObject(renderer, imagePath, Vector2D((start_position.x * 16) - offsetX, (start_position.y * 16) - offsetY), offsetX, offsetY, lengthX, lengthY)
{
	player = character;
}
LoadingZone::~LoadingZone()
{
	player = nullptr;
}

bool LoadingZone::Update(float deltaTime, SDL_Event e)
{
	if (Collisions::Instance()->Box(this, player))
	{
		return true;
	}
	return false;
}