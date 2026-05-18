#include "Wall.h"

#include "Collisions.h"

Wall::Wall(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, int offsetX, int offsetY, int lengthX, int lengthY) : GameObject(renderer, imagePath, Vector2D((start_position.x * 16) - offsetX, (start_position.y * 16) - offsetY), offsetX, offsetY, lengthX, lengthY) {}
Wall::~Wall() {}

bool Wall::Update(float deltaTime, SDL_Event e, GameObject* other)
{
	if (Collisions::Instance()->BoxBlock(other, this, deltaTime) == COLLISION_DOWN)
	{
		return true; //returns true if other is on ground
	}
	return false;
}